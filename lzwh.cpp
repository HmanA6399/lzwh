#include "functions.cpp"
#include "compressor.cpp"

int main(int argc, char **argv)
{
  // Speed-up in/out
  // ios_base::sync_with_stdio(false);
  // cin.tie(NULL);

  if (strcmp(argv[1], "help") == 0)
  {
    cout << "lzwh 1.0.0 Compression Algorithm\n"
         << "Syntax : \n\tlzwh OPTION FILE\n"
         << "Options:-\n"
         << "\te\tencode\n\td\tdecode\n";
    return 0;
  }

  if (argc != 3)
  {
    cout << "ERROR: Invalid input\nRun \"lzwh help\" for help\n";
    return 1;
  }

  if (strcmp(argv[1], "e") == 0)
  {
    Compressor enc(argv[2], "out.lzwh");
    enc.encode();
  }
  else if (strcmp(argv[1], "d") == 0)
  {
    Compressor dec(argv[2], "out");
    dec.decode();
  }
}