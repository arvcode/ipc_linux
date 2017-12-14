/* GPL
 * Taken from Advanced Linux Programming
 * The source code contained in this book is covered by the GNU General Public License
   (GPL), which is listed in Appendix F,.GNU General Public License.
 */

#include <stdio.h>
#include <tiffio.h>
int main (int argc, char** argv)
{
TIFF* tiff;
tiff = TIFFOpen (argv[1], 'r');
TIFFClose (tiff);
return 0;
}
