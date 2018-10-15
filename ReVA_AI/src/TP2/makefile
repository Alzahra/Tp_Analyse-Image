OPENCV_LIBS = -L../../lib/ -lIlmImf -llibtiff -lopencv_imgcodecs -lippicv -llibwebp -lopencv_imgproc -llibjasper -lopencv_core -lzlib -llibjpeg -lopencv_hal -llibpng -lopencv_highgui
OSX_LIBS = -framework OpenCL -framework Cocoa
INC = -I../../include/
 
all : image_expansion
 

image_expansion: compute_histogram.cpp image_expansion.cpp main.cpp
	$(CXX) -o image_expansion compute_histogram.cpp image_expansion.cpp main.cpp $(INC) $(OSX_LIBS) $(OPENCV_LIBS)

 
clean :
	rm image_expansion