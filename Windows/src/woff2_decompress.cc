/* Copyright 2013 Google Inc. All Rights Reserved.

   Distributed under MIT license.
   See file LICENSE for detail or copy at https://opensource.org/licenses/MIT
*/

/* A very simple commandline tool for decompressing woff2 format files to true
   type font files. */

#include <string>

#include "./file.h"
#include <woff2/decode.h>


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
  std::string outfilename = filename.substr(0, filename.find_last_of(".")) + ".ttf";

    fprintf(stderr, "\n");
    fprintf(stderr, "++++++++++++++++++++++++++++++++++++++\n");
    fprintf(stdout, "Abdal TTF WOFF2 Processing %s => %s\nProgrammer Ebrahim Shafiei\n+98 09022223301\nProf.Shafiei@Gmail.com\nhttps://hackers.zone/\n",filename.c_str(), outfilename.c_str());
    fprintf(stderr, "++++++++++++++++++++++++++++++++++++++\n");

  // Note: update woff2_dec_fuzzer_new_entry.cc if this pattern changes.
  std::string input = woff2::GetFileContent(filename);
  const uint8_t* raw_input = reinterpret_cast<const uint8_t*>(input.data());
  std::string output(
      std::min(woff2::ComputeWOFF2FinalSize(raw_input, input.size()),
               woff2::kDefaultMaxSize),
      0);
  woff2::WOFF2StringOut out(&output);

  const bool ok = woff2::ConvertWOFF2ToTTF(raw_input, input.size(), &out);

  if (ok) {
    woff2::SetFileContents(outfilename, output.begin(),
        output.begin() + out.Size());
  }
  return ok ? 0 : 1;
}
