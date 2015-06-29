# On OpenNAO/NAO OS, execute the following to apply the patch
cd /source/human-robot-interaction
sudo cp lib/libstdc++.so.6.0.16 /usr/lib
sudo rm libstdc++.so
sudo ln -s libstdc++.so.6.0.16 libstdc++.so

# This command should show versions upto GLIBCXX_3.4.16
strings /usr/lib/libstdc++.so.6 | grep GLIBC