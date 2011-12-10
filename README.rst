************************
 HPX Build Instructions 
************************

Linux
-----

1) Download the latest Subversion revision of HPX (or a stable tag):::

    $ svn co https://svn.cct.lsu.edu/repos/projects/parallex/trunk/hpx hpx

2) Create a build directory. HPX requires an out-of-tree build. This means you
   will be unable to run CMake in the HPX source directory.::
  
    $ cd hpx
    $ mkdir my_hpx_build
    $ cd my_hpx_build

3) Invoke CMake from your build directory, pointing the CMake driver to the root
   of your HPX source tree.::

    $ cmake [CMake variable definitions] /path/to/source/tree 

4) Invoke GNU make. If you are on a box with multiple cores (very likely),
   add the -jN flag to your make invocation, where N is the number of nodes
   on your machine plus one.::

    $ gmake -j49
 
5) To complete the build and install HPX:::

    $ gmake install

Windows
-------

1) Download the latest Subversion revision of HPX (or a stable tag). You can
   use TortoiseSVN, or the subversion client that Cygwin provides. The latest
   subversion revision can be found at:::

    https://svn.cct.lsu.edu/repos/projects/parallex/trunk/hpx

2) Create a build folder. HPX requires an out-of-tree-build. This means that you
   will be unable to run CMake in the HPX source folder.

3) Open up the CMake GUI. In the input box labelled "Where is the source code:",
   enter the full path to the source folder. In the input box labelled
   "Where to build the binaries:", enter the full path to the build folder you
   created in step 1.

4) Add CMake variable definitions (if any) by clicking the "Add Entry" button.

5) Press the "Configure" button. A window will pop up asking you which compilers
   to use. Select the x64 Visual Studio 10 compilers (they are usually the
   default if available).

6) If the "Generate" button is not clickable, press "Configure" again. Repeat
   this step until the "Generate" button becomes clickable.

7) Press "Generate".

8) Open up the build folder, and double-click hpx.sln.

9) Build the INSTALL target.

