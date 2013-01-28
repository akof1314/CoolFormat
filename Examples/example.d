import file;

 int main (char[][] args)
 {
     int w_total;
     int l_total;
     int c_total;
     int[char[]] dictionary;

      printf("    lines    words    bytes file\n");
     for (int i = 1; i < args.length; ++i)
      {
  char[] input;
  int w_cnt, l_cnt, c_cnt;
  int inword;
  int wstart;

  input = cast(char[])file.read(args[i]);

  for (int j = 0; j < input.length; j++)
  {   char c;

       c = input[j];
      if (c == '\n')
   ++l_cnt;
      if (c >= '0' && c <= '9')
       {
       }
      else if (c >= 'a' && c <= 'z' ||
   c >= 'A' && c <= 'Z')
       {
   if (!inword)
   {
        wstart = j;
        inword = 1;
        ++w_cnt;
   }
       }
      else if (inword)
       {   char[] word = input[wstart .. j];

   dictionary[word]++;
   inword = 0;
       }
       ++c_cnt;
  }
  if (inword)
  {   char[] w = input[wstart .. input.length];
       dictionary[w]++;
  }
  printf("%8lu%8lu%8lu %.*s\n", l_cnt, w_cnt, c_cnt, args[i]);
  l_total += l_cnt;
  w_total += w_cnt;
  c_total += c_cnt;
      }

     if (args.length > 2)
      {
  printf("--------------------------------------\n%8lu%8lu%8lu total",
       l_total, w_total, c_total);
      }

      printf("--------------------------------------\n");

     foreach (char[] word1; dictionary.keys.sort)
      {
  printf("%3d %.*s\n", dictionary[word1], word1);
      }
     return 0;
 }