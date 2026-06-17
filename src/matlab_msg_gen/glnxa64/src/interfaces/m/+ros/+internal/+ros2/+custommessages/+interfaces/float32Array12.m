function [data, info] = float32Array12
%Float32Array12 gives an empty data for interfaces/Float32Array12
% Copyright 2019-2021 The MathWorks, Inc.
data = struct();
data.MessageType = 'interfaces/Float32Array12';
[data.data, info.data] = ros.internal.ros2.messages.ros2.default_type('single',12,0);
info.MessageType = 'interfaces/Float32Array12';
info.constant = 0;
info.default = 0;
info.maxstrlen = NaN;
info.MaxLen = 1;
info.MinLen = 1;
info.MatPath = cell(1,1);
info.MatPath{1} = 'data';
