render_width = 640;
render_height = 480;
model_name = '3DModels/Faces/Model_2/3DScan.obj';
features_filename = 'features.txt';

%% STEP 1 - RENDER 3D REFERENCE MODEL, DETECT SPECIFIC FACIAL FEATURES, GET THEIR 3D COORDINATES ON THE 3D MODEL
% render 
[refD, refI, refU, outA, outR, outT] = renderer(render_width, render_height, model_name, 0, 1, 1, 0, 0, 0, 'zxy'); 
% detect facial features on the rendered image, code from www.ics.uci.edu/~xzhu/face/ with modifications to get center of detection window (detect parameters taken from their code)
ref_bs = detect(refI, model, model.thresh);
ref_bs = clipboxes(refI, ref_bs);
ref_bs = nms_face(ref_bs,0.3);
x1 = ref_bs.xy(:,1);
y1 = ref_bs.xy(:,2);
x2 = ref_bs.xy(:,3);
y2 = ref_bs.xy(:,4);
ref_XY = [(x1+x2)/2,(y1+y2)/2];
% get 3D coordinates of facial features, using the refU map from image 2D to model 3D
ind = sub2ind([size(refU,1), size(refU,2)], round(ref_XY(:,2)), round(ref_XY(:,1)));
threedee = zeros(numel(ind),3);
tmp = refU(:,:,1);
threedee(:,1) = tmp(ind);
tmp = refU(:,:,2);
threedee(:,2) = tmp(ind);
tmp = refU(:,:,3);
threedee(:,3) = tmp(ind);
% a bit of sanity
indbad = find(max(threedee,[],2)==0);
threedee(indbad,:)=[];


%% STEP 2 - LOAD QUERY IMAGE, DETECT ITS FACIAL FEATURES
queryI = imread(filen);
img_bs = detect(queryI, model, model.thresh);
img_bs = clipboxes(queryI, img_bs);
img_bs = nms_face(img_bs,0.3);
x1 = img_bs.xy(:,1);
y1 = img_bs.xy(:,2);
x2 = img_bs.xy(:,3);
y2 = img_bs.xy(:,4);
img_XY = [(x1+x2)/2,(y1+y2)/2];
img_XY(indbad,:)=[];


%% STEP 3 - COMPUTE POSE USING REFERENCE 3D POINTS + QUERY 2D POINTS, AND RE-RENDER
% Estimate pose
[est_A,est_R,est_T] = doCalib(size(refU,2), size(refU,1), img_XY, threedee, outA, [], []);
% re-render reference to the same pose as query. Note the change in input and output parameters vs. the previous call. Also note that the model file is not reloaded and a cached version is used instead.
[refD, refI, unproject_est] = renderer(render_width, render_height, model_name, 0, 1, est_A, est_R, est_T);  