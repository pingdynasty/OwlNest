/* This implements the ST Microsystems DFU extensions (DfuSe)
 * as per the DfuSe 1.1a specification (Document UM0391)
 *
 * (C) 2010-2012 Tormod Volden <debian.tormod@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef DFUSELOADER_H
#define DFUSELOADER_H

#include "JuceHeader.h"

extern "C" {
#include "dfu.h"
enum dfuse_command { SET_ADDRESS, ERASE_PAGE, MASS_ERASE, READ_UNPROTECT };
}

class DfuseLoader {
public:
  DfuseLoader(ThreadWithProgressWindow* win);
  int dfuse_special_command(struct dfu_if *dif, unsigned int address,
			    enum dfuse_command command);
  int do_upload(struct dfu_if *dif, int xfer_size, int fd,
		      const char *dfuse_options);
  int do_dnload(struct dfu_if *dif, int xfer_size, struct dfu_file *file,
		      const char *dfuse_options);
  String getMessage();
private:
  void dfuse_parse_options(const char *options);
  int dfuse_upload(struct dfu_if *dif, const unsigned short length,
		   unsigned char *data, unsigned short transaction);
  int dfuse_download(struct dfu_if *dif, const unsigned short length,
		     unsigned char *data, unsigned short transaction);
  int dfuse_dnload_chunk(struct dfu_if *dif, unsigned char *data, int size,
			 int transaction);
  int dfuse_dnload_element(struct dfu_if *dif, unsigned int dwElementAddress,
			   unsigned int dwElementSize, unsigned char *data,
			   int xfer_size);
  void dfuse_memcpy(unsigned char *dst, unsigned char **src, int *rem, int size);
  int dfuse_do_bin_dnload(struct dfu_if *dif, int xfer_size,
			  struct dfu_file *file, unsigned int start_address);
  int dfuse_do_dfuse_dnload(struct dfu_if *dif, int xfer_size,
			    struct dfu_file *file);

  void errx(int errid, const String& msg);
  ThreadWithProgressWindow* alert;
  String message;
};

#endif /* DFUSELOADER_H */
