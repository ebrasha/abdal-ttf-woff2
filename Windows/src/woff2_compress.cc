/* Copyright 2013 Google Inc. All Rights Reserved.

   Distributed under MIT license.
   See file LICENSE for detail or copy at https://opensource.org/licenses/MIT
*/

/* A commandline tool for compressing ttf format files to woff2. */

#include <string>

#include "file.h"
#include <woff2/encode.h>


int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "The argument must be the input filename.\n");
    fprintf(stderr, "Programmer Ebrahim Shafiei (EbraSha)\n");
    fprintf(stderr, "+98 09022223301\n");
    fprintf(stderr, "Prof.Shafiei@Gmail.com\n");
    fprintf(stderr, "https://hackers.zone/\n");
    return 1;
  }

  std::string filename(argv[1]);
  std::string outfilename = filename.substr(0, filename.find_last_of(".")) + ".woff2";
  fprintf(stderr, "\n");
  fprintf(stderr, "++++++++++++++++++++++++++++++++++++++\n");
  fprintf(stdout, "Abdal TTF WOFF2 Processing %s => %s\nProgrammer Ebrahim Shafiei\n+98 09022223301\nProf.Shafiei@Gmail.com\nhttps://hackers.zone/\n",
    filename.c_str(), outfilename.c_str());
  std::string input = woff2::GetFileContent(filename);
  fprintf(stderr, "++++++++++++++++++++++++++++++++++++++\n");

  const uint8_t* input_data = reinterpret_cast<const uint8_t*>(input.data());
  size_t output_size = woff2::MaxWOFF2CompressedSize(input_data, input.size());
  std::string output(output_size, 0);
  uint8_t* output_data = reinterpret_cast<uint8_t*>(&output[0]);

  woff2::WOFF2Params params;
  if (!woff2::ConvertTTFToWOFF2(input_data, input.size(),
                                output_data, &output_size, params)) {
    fprintf(stderr, "Compression failed.\n");
    return 1;
  }
  output.resize(output_size);

  woff2::SetFileContents(outfilename, output.begin(), output.end());

  return 0;
}
