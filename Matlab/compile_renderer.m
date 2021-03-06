%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%  Modified by Chao Yao
%  compile the C++ code  to .mexw64 file to use in matlab 2013a 64bit
%  make sure that your OpensceneGraph is x64 version and can run successfully
%  edit the libpath and incpath to your OSG installation directory
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% clc
cmd1='mex -O -largeArrayDims -DA64BITS renderer.cpp depth.cpp Engine.cpp EngineOSG.cpp util.cpp -lOpenGL32 -lglu32 -losg -losgViewer -losgDB -losgGA -losgUtil -lOpenThreads';

libpath=fullfile('C:\Projects\OpenSceneGraph\OpenSceneGraph-OpenSceneGraph-3.6.0\build\','lib');
incpath=fullfile('C:\Projects\OpenSceneGraph\OpenSceneGraph-OpenSceneGraph-3.6.0\build\','include');
dllpath=fullfile('C:\Projects\OpenSceneGraph\OpenSceneGraph-OpenSceneGraph-3.6.0\build\bin');

cmd=[cmd1 sprintf(' -L%s -I%s -D%s',libpath,incpath,dllpath)];
%cmd=[cmd1 sprintf(' -L%s -I%s',libpath,incpath)];

disp('Executing:');
fprintf('%s\n',cmd);
eval(cmd);
