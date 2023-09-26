root -b -l << EOF
#include "CondFormats/Common/interface/TimeConversions.h"
cond::time::pack({$1, $2})
cond::time::pack({$3, $4})
EOF
