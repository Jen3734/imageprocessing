This project impelements a mid-scale real-time image processing workflow under MIT license. The project utilize Windows CPU memory handling and all written in C++17. The CPU memory handling can be changed to GPU memory handling easily. We will bring further update on that.

The design is illustrated here:

![image_processing worflow design](./readMe/image_processing_design.drawio.png)

There are couple of parameters to be set:

```
int ImageSize = 100; // under RequestEvent.h
int SingleImageJobSize = 3; // under JobEvent.h
```

It can be easily packaged into a service by wrapping in http server and RESTFUL API.
