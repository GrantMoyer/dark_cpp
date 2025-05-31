#pragma once
#if defined _WIN32 || defined __CYGWIN__
  #ifdef BUILDING_DARK_C__
    #define DARK_C___PUBLIC __declspec(dllexport)
  #else
    #define DARK_C___PUBLIC __declspec(dllimport)
  #endif
#else
  #ifdef BUILDING_DARK_C__
      #define DARK_C___PUBLIC __attribute__ ((visibility ("default")))
  #else
      #define DARK_C___PUBLIC
  #endif
#endif

namespace dark_c__ {

class DARK_C___PUBLIC Dark_c__ {

public:
  Dark_c__();
  int get_number() const;

private:

  int number;

};

}

