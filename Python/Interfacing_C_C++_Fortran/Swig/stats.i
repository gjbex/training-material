%module stats
%{
#include "stats.h"
%}

%include "carrays.i"
%array_class(double, floatArray)
%include "stats.h"

