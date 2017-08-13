#include <iostream>
#include <fstream>
#include <unordered_map>
#include <boost/tokenizer.hpp>
#include <boost/program_options.hpp>
#include <boost/thread.hpp>
#include <boost/chrono.hpp>

typedef std::unordered_map<std::string, int> wc_dictionary;
typedef boost::tokenizer<boost::char_separator<char>> tokenizer;

std::ifstream ifs;
wc_dictionary dict;

void pack ()
{
  std::string buffer;
  ifs.open ("../hogehoge.txt", std::ifstream::in);

  if (ifs.fail () == true)
    {
      std::cerr << "cannot open file" << std::endl;
      return;
    }

  boost::char_separator<char> sep (" ");

  while (!ifs.eof ())
    {
      std::getline (ifs, buffer);
      tokenizer tokens (buffer, sep);
      for (auto i: tokens)
        {
          dict[i]++;
        }
    }
  ifs.close ();
}

void tell_size ()
{
  while (true)
    {
      sleep (1);
      if (ifs.eof ())
        {
          return;
        }
      std::cout << dict.size () << " at " << ifs.tellg () << std::endl;
      boost::this_thread::yield ();
    }
}

void open ()
{
  boost::thread_group threads;

  threads.create_thread (boost::ref (pack));
  threads.create_thread (boost::ref (tell_size));

  threads.join_all ();
}

int main ()
{
  open ();

  for (auto x: dict)
    {
      std::cout << x.first << " = " << x.second << std::endl;
    }
  return 0;
}
