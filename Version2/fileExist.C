/////////////////////////////////////////////////////////////////
// bool fileExists( std::string const& name ); verifica si un //     
// archico o carpeta existe                                   //
////////////////////////////////////////////////////////////////

#include <iostream>
#include <string> 
#include <stdio.h>
#include <sys/stat.h>

bool fileExists( std::string const& name )
{
  struct stat buffer;   
  return (stat(name.c_str(), &buffer) == 0); 
}
