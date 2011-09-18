#pragma once

#include <vector>
#include <string>
#include <io.h>


// ディレクトリ以下のファイルを列挙
std::vector< std::string > enumerateFiles( const std::string directory )
{
  std::vector< std::string > files;

  struct _finddata_t c_file;

  long hFile = _findfirst( ( directory + "/*").c_str(), &c_file );
  if( hFile == -1 )
  {
    return files;
  }

  while( _findnext( hFile, &c_file ) == 0 )
  {
    std::string filename( c_file.name );
    if( filename == "." || filename == ".." )
    {
      continue;
    }

    files.push_back( filename );

  }

  _findclose( hFile );

  return files;
}