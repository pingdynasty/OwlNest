#include "FirmwareLoader.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#define __GNU_LIBRARY__
#include <getopt.h>

#ifdef _MSC_VER
#include <wchar.h>
#include <io.h>
#define open _open
#define close _close
#define _SSIZE_T_DEFINED // Need to test if useful in non-VS project
#else
#include <unistd.h>
#endif

#include <libusb.h>

extern "C" {
#include <dfu-util/portable.h>
#include <dfu-util/dfu.h>
#include <dfu-util/usb_dfu.h>
#include <dfu-util/dfu_file.h>
#include <dfu-util/dfu_load.h>
#include <dfu-util/dfu_util.h>
#include <dfu-util/dfuse.h>
#include <dfu-util/quirks.h>

  int verbose = 0;
  struct dfu_if *dfu_root;
  int match_bus = -1;
  int match_device = -1;
  int match_vendor = -1;
  int match_product = -1;
  int match_vendor_dfu = -1;
  int match_product_dfu = -1;
  int match_config_index = -1;
  int match_iface_index = -1;
  int match_iface_alt_index = -1;
  const char *match_iface_alt_name;
  const char *match_serial;
  const char *match_serial_dfu;

  libusb_context *ctx;
  struct dfu_status status;
  int dfuse_device;
  const char *dfuse_options;
  struct dfu_file file;
  int mode;
  uint16_t runtime_vendor;
  uint16_t runtime_product;
  unsigned int transfer_size;
}

FirmwareLoader::FirmwareLoader() : message("OK") {
}

String FirmwareLoader::getMessage(){
  return message;
}

bool FirmwareLoader::init(const File& firmware, const String& options){
  int dfu_has_suffix = 0;
  transfer_size = 0;
  dfuse_options = NULL;
  dfu_root = NULL;
  ctx = NULL;

  // dfu-util -d 0483:df11 -c 1 -i 0 -a 0 -s 0x8000000 -D foo.bin
  match_vendor = 0x0483; // -d nn:
  match_product = 0xdf11; // -d :nn
  match_config_index = 1; // -c n
  match_iface_index = 0; // -i n
  match_iface_alt_index = 0; // -a n
  dfuse_options = options.toUTF8(); // -s ccc
  mode = MODE_DOWNLOAD;

  memset(&file, 0, sizeof(file));
  file.name = firmware.getFullPathName().toUTF8();

  if (mode == MODE_DOWNLOAD) {
    dfu_load_file(&file, dfu_has_suffix, 0);
    /* If the user didn't specify product and/or vendor IDs to match,
     * use any IDs from the file suffix for device matching */
    if (match_vendor < 0 && file.idVendor != 0xffff) {
      match_vendor = file.idVendor;
      printf("Match vendor ID from file: %04x\n", match_vendor);
    }
    if (match_product < 0 && file.idProduct != 0xffff) {
      match_product = file.idProduct;
      printf("Match product ID from file: %04x\n", match_product);
    }
  }
  int ret = libusb_init(&ctx);
  if (ret){
    errx(EX_IOERR, String::formatted("unable to initialize libusb: %i", ret));
    return false;
  }
  if (verbose > 2) {
    libusb_set_debug(ctx, 255);
  }
  return true;
}

bool FirmwareLoader::probeDevices(){
  probe_devices(ctx);
  return dfu_root != NULL;
}

void FirmwareLoader::listDevices(){
  list_dfu_interfaces();
}

bool FirmwareLoader::openDevice(){
  // progress = 0.0;

  // probe_devices(ctx);

  // if (mode == MODE_LIST) {
  //   list_dfu_interfaces();
  //   return 0;
  // }

  // for(int i=0; i<20 && dfu_root == NULL; ++i) {
  //   progress += 0.005;
  //   printf("probing for DFU device...\n");
  //   milli_sleep(500);
  //   probe_devices(ctx);
  // }

  if (dfu_root == NULL) {
    errx(EX_IOERR, "No DFU capable USB device found");
    return false;
  } else if (dfu_root->next != NULL) {
    /* We cannot safely support more than one DFU capable device
     * with same vendor/product ID, since during DFU we need to do
     * a USB bus reset, after which the target device will get a
     * new address */
    errx(EX_IOERR, "More than one DFU capable USB device found! "
	 "Try `--list' and specify the serial number "
	 "or disconnect all but one device\n");
    return false;
  }

  /* We have exactly one device. Its libusb_device is now in dfu_root->dev */

  printf("Opening DFU capable USB device...\n");
  int ret = libusb_open(dfu_root->dev, &dfu_root->dev_handle);
  if(ret || !dfu_root->dev_handle){
    errx(EX_IOERR, "Cannot open device");
    return false;
  }
  return true;
}

bool FirmwareLoader::connectToDevice(){
  int detach_delay = 5;

  if(!dfu_root->dev_handle){
    errx(EX_IOERR, "Cannot open device");
    return false;
  }

  printf("ID %04x:%04x\n", dfu_root->vendor, dfu_root->product);

  printf("Run-time device DFU version %04x\n",
	 libusb_le16_to_cpu(dfu_root->func_dfu.bcdDFUVersion));

  /* Transition from run-Time mode to DFU mode */
  if (!(dfu_root->flags & DFU_IFF_DFU)) {
    int err;
    /* In the 'first round' during runtime mode, there can only be one
     * DFU Interface descriptor according to the DFU Spec. */

    /* FIXME: check if the selected device really has only one */

    runtime_vendor = dfu_root->vendor;
    runtime_product = dfu_root->product;

    printf("Claiming USB DFU Runtime Interface...\n");
    if (libusb_claim_interface(dfu_root->dev_handle, dfu_root->interface) < 0) {
      errx(EX_IOERR, String::formatted("Cannot claim interface %d", dfu_root->interface));
      return -1;
    }

    if (libusb_set_interface_alt_setting(dfu_root->dev_handle, dfu_root->interface, 0) < 0) {
      errx(EX_IOERR, "Cannot set alt interface zero");
    }

    printf("Determining device status: ");

    err = dfu_get_status(dfu_root->dev_handle, dfu_root->interface, &status);
    if (err == LIBUSB_ERROR_PIPE) {
      printf("Device does not implement get_status, assuming appIDLE\n");
      status.bStatus = DFU_STATUS_OK;
      status.bwPollTimeout = 0;
      status.bState  = DFU_STATE_appIDLE;
      status.iString = 0;
    } else if (err < 0) {
      errx(EX_IOERR, "error get_status");
      return false;
    } else {
      printf("state = %s, status = %d\n",
	     dfu_state_to_string(status.bState), status.bStatus);
    }

    if (!(dfu_root->quirks & QUIRK_POLLTIMEOUT))
      milli_sleep((long) status.bwPollTimeout);

    switch (status.bState) {
    case DFU_STATE_appIDLE:
    case DFU_STATE_appDETACH:
      printf("Device really in Runtime Mode, send DFU "
	     "detach request...\n");
      if (dfu_detach(dfu_root->dev_handle,
		     dfu_root->interface, 1000) < 0) {
	errx(EX_IOERR, "error detaching");
	return false;
      }
      libusb_release_interface(dfu_root->dev_handle,
			       dfu_root->interface);
      if (dfu_root->func_dfu.bmAttributes & USB_DFU_WILL_DETACH) {
	printf("Device will detach and reattach...\n");
      } else {
	printf("Resetting USB...\n");
	int ret = libusb_reset_device(dfu_root->dev_handle);
	if (ret < 0 && ret != LIBUSB_ERROR_NOT_FOUND){
	  errx(EX_IOERR, "error resetting "
	       "after detach");
	  return false;
	}
      }
      break;
    case DFU_STATE_dfuERROR:
      printf("dfuERROR, clearing status\n");
      if (dfu_clear_status(dfu_root->dev_handle,
			   dfu_root->interface) < 0) {
	errx(EX_IOERR, "error clear_status");
	return false;
      }
      /* fall through */
    default:
      warnx("WARNING: Runtime device already in DFU state ?!?");
      goto dfustate;
      break;
    }

    libusb_release_interface(dfu_root->dev_handle,
			     dfu_root->interface);
    libusb_close(dfu_root->dev_handle);
    dfu_root->dev_handle = NULL;

    if (mode == MODE_DETACH) {
      libusb_exit(ctx);
      return true;
    }

    /* keeping handles open might prevent re-enumeration */
    disconnect_devices();

    milli_sleep(detach_delay * 1000);

    /* Change match vendor and product to impossible values to force
     * only DFU mode matches in the following probe */
    match_vendor = match_product = 0x10000;

    probe_devices(ctx);

    if (dfu_root == NULL) {
      errx(EX_IOERR, "Lost device after RESET?");
      return false;
    } else if (dfu_root->next != NULL) {
      errx(EX_IOERR, "More than one DFU capable USB device found! "
	   "Try `--list' and specify the serial number "
	   "or disconnect all but one device");
      return false;
    }

    /* Check for DFU mode device */
    if (!(dfu_root->flags |= DFU_IFF_DFU)){
      errx(EX_SOFTWARE, "Device is not in DFU mode");
      return false;
    }

    printf("Opening DFU USB Device...\n");
    int ret = libusb_open(dfu_root->dev, &dfu_root->dev_handle);
    if (ret || !dfu_root->dev_handle) {
      errx(EX_IOERR, "Cannot open device");
      return false;
    }
  } else {
    /* we're already in DFU mode, so we can skip the detach/reset
     * procedure */
    /* If a match vendor/product was specified, use that as the runtime
     * vendor/product, otherwise use the DFU mode vendor/product */
    runtime_vendor = match_vendor < 0 ? dfu_root->vendor : match_vendor;
    runtime_product = match_product < 0 ? dfu_root->product : match_product;
  }

 dfustate:
#if 0
  printf("Setting Configuration %u...\n", dfu_root->configuration);
  if (libusb_set_configuration(dfu_root->dev_handle, dfu_root->configuration) < 0) {
    errx(EX_IOERR, "Cannot set configuration");
    return false;
  }
#endif
  printf("Claiming USB DFU Interface...\n");
  if (libusb_claim_interface(dfu_root->dev_handle, dfu_root->interface) < 0) {
    errx(EX_IOERR, "Cannot claim interface");
    return false;
  }

  printf("Setting Alternate Setting #%d ...\n", dfu_root->altsetting);
  if (libusb_set_interface_alt_setting(dfu_root->dev_handle, dfu_root->interface, dfu_root->altsetting) < 0) {
    errx(EX_IOERR, "Cannot set alternate interface");
    return false;
  }

 status_again:
  printf("Determining device status: ");
  if (dfu_get_status(dfu_root->dev_handle, dfu_root->interface, &status ) < 0) {
    errx(EX_IOERR, "error get_status");
    return false;
  }
  printf("state = %s, status = %d\n",
	 dfu_state_to_string(status.bState), status.bStatus);
  if (!(dfu_root->quirks & QUIRK_POLLTIMEOUT))
    milli_sleep((long) status.bwPollTimeout);

  switch (status.bState) {
  case DFU_STATE_appIDLE:
  case DFU_STATE_appDETACH:
    errx(EX_IOERR, "Device still in Runtime Mode!");
    return false;
    break;
  case DFU_STATE_dfuERROR:
    printf("dfuERROR, clearing status\n");
    if (dfu_clear_status(dfu_root->dev_handle, dfu_root->interface) < 0) {
      errx(EX_IOERR, "error clear_status");
      return false;
    }
    goto status_again;
    break;
  case DFU_STATE_dfuDNLOAD_IDLE:
  case DFU_STATE_dfuUPLOAD_IDLE:
    printf("aborting previous incomplete transfer\n");
    if (dfu_abort(dfu_root->dev_handle, dfu_root->interface) < 0) {
      errx(EX_IOERR, "can't send DFU_ABORT");
      return false;
    }
    goto status_again;
    break;
  case DFU_STATE_dfuIDLE:
    printf("dfuIDLE, continuing\n");
    break;
  default:
    break;
  }

  if (DFU_STATUS_OK != status.bStatus ) {
    printf("WARNING: DFU Status: '%s'\n",
	   dfu_status_to_string(status.bStatus));
    /* Clear our status & try again. */
    if (dfu_clear_status(dfu_root->dev_handle, dfu_root->interface) < 0){
      errx(EX_IOERR, "USB communication error");
      return false;
    }if (dfu_get_status(dfu_root->dev_handle, dfu_root->interface, &status) < 0){
      errx(EX_IOERR, "USB communication error");
      return false;
    }if (DFU_STATUS_OK != status.bStatus){
      errx(EX_SOFTWARE, String::formatted("Status is not OK: %d", status.bStatus));
      return false;
    }if (!(dfu_root->quirks & QUIRK_POLLTIMEOUT)){
      milli_sleep((long) status.bwPollTimeout);
    }
  }

  printf("DFU mode device DFU version %04x\n",
	 libusb_le16_to_cpu(dfu_root->func_dfu.bcdDFUVersion));

  if (dfu_root->func_dfu.bcdDFUVersion == libusb_cpu_to_le16(0x11a))
    dfuse_device = 1;
  else
    dfuse_device = 0;

  /* If not overridden by the user */
  if (!transfer_size) {
    transfer_size = libusb_le16_to_cpu(
				       dfu_root->func_dfu.wTransferSize);
    if (transfer_size) {
      printf("Device returned transfer size %i\n",
	     transfer_size);
    } else {
      errx(EX_IOERR, "Transfer size must be "
	   "specified");
      return false;
    }
  }

#ifdef HAVE_GETPAGESIZE
  /* autotools lie when cross-compiling for Windows using mingw32/64 */
#ifndef __MINGW32__
  /* limitation of Linux usbdevio */
  if ((int)transfer_size > getpagesize()) {
    transfer_size = getpagesize();
    printf("Limited transfer size to %i\n", transfer_size);
  }
#endif /* __MINGW32__ */
#endif /* HAVE_GETPAGESIZE */

  if (transfer_size < dfu_root->bMaxPacketSize0) {
    transfer_size = dfu_root->bMaxPacketSize0;
    printf("Adjusted transfer size to %i\n", transfer_size);
  }

  return true;
}

bool FirmwareLoader::loadFromDevice(){
  int expected_size = 0;
  /* open for "exclusive" writing */
  int fd = open(file.name, O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0666);
  if (fd < 0)
    err(EX_IOERR, "Cannot open file %s for writing", file.name);
  
  if (dfuse_device || dfuse_options) {
    if (dfuse_do_upload(dfu_root, transfer_size, fd,
			dfuse_options) < 0)
      return true;
  } else {
    if (dfuload_do_upload(dfu_root, transfer_size,
			  expected_size, fd) < 0) {
      return true;
    }
  }
  close(fd);
  return true;
}

bool FirmwareLoader::loadToDevice(){
  if (((file.idVendor  != 0xffff && file.idVendor  != runtime_vendor) ||
       (file.idProduct != 0xffff && file.idProduct != runtime_product)) &&
      ((file.idVendor  != 0xffff && file.idVendor  != dfu_root->vendor) ||
       (file.idProduct != 0xffff && file.idProduct != dfu_root->product))) {
    errx(EX_IOERR, String::formatted("Error: File ID %04x:%04x does "
				     "not match device (%04x:%04x or %04x:%04x)",
				     file.idVendor, file.idProduct,
				     runtime_vendor, runtime_product,
				     dfu_root->vendor, dfu_root->product));
    return false;
  }
  if (dfuse_device || dfuse_options || file.bcdDFU == 0x11a) {
    if (dfuse_do_dnload(dfu_root, transfer_size, &file,
			dfuse_options) < 0)
      return true;
  } else {
    if (dfuload_do_dnload(dfu_root, transfer_size, &file) < 0)
      return true;
  }
  return true;
}

bool FirmwareLoader::detachDevice(){
  if (dfu_detach(dfu_root->dev_handle, dfu_root->interface, 1000) < 0) {
    errx(EX_IOERR, "can't detach");
    return false;
  }
  return true;
}

bool FirmwareLoader::resetDevice(){
  if (dfu_detach(dfu_root->dev_handle, dfu_root->interface, 1000) < 0) {
    //       errx(EX_IOERR, "can't detach");
    warnx("can't detach");
  }
  printf("Resetting USB to switch back to runtime mode\n");
  int ret = libusb_reset_device(dfu_root->dev_handle);
  if (ret < 0 && ret != LIBUSB_ERROR_NOT_FOUND) {
    errx(EX_IOERR, "error resetting after download");
    return false;
  }
  return true;
}

bool FirmwareLoader::closeDevice(){
  libusb_close(dfu_root->dev_handle);
  dfu_root->dev_handle = NULL;
  libusb_exit(ctx);
  return true;
}

void FirmwareLoader::errx(int errid, const String& msg){
  DBG(msg);
  message = msg;
}
