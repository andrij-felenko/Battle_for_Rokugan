 git log --pretty=format:==%an --numstat |  sed -r '/==.*/{s/^==//;h;D};/^$/D;s/-/0/g;s/\t[^\t]+$//;G;s/(.*)\n(.*)/\2\t\1/'  | awk -F '\t' '{add[$1]+=$2;del[$1]+=$3} END {print "Diff history:"; addS = 0;delS = 0; for (i in add) { addS+=add[i]; delS += del[i]; print i, "+:"add[i],"-:"del[i],"diff:"add[i]-del[i]} print "\nTotal:\nadd line = ",addS, "\ndelete line = ", delS, "\ndiff lines = ", addS-delS}'
