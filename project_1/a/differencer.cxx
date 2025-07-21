#include <iostream>
#include <vtkDataSet.h>
#include <vtkImageData.h>
#include <vtkPNGWriter.h>
#include <vtkPointData.h>
#include <vtkPNGRreader.h>
//vtk stands for visualization toolkit


using std::cerr;
using std::endl;

vtkImageData *
NewImage(int width, int height){

    vtkImageData *ing = vtkImageData::New();
    img->setDimensions(width, height, 1);
    //img->setNumberOfScalarComponents(3);
    //img->setScalarTypeToUnsignedChar();
    img->AllocateScalars(VTK_UNSIGNED_CHAR, 3);

    return img;
}

void 
WriteImage(vtkImageData *img, const char *filename){

    std::string full_filename = filename;
    full_filename += ".png";
    vtkPNGWriter *writer = vtkPNGWriter::New();
    writer->SetInputData(img);
    writer->SetFileName(full_filename.c_str());
    writer->Write();
    writer->Delete();
}


vtkImageData * 
ReadImage(const std::string &filename){

    vtkPNGReader *reader = vtkPNGReader::New();
    reader->SetFileName(filename.c_str());
    reader->Update();

    if (reader->GetOutput() == NULL || 
	reader->GetOutput()->GetNumberOfCells() == 0){

	cerr << "not able to read image" << endl;
	exit(1);// 1 means error here
    }
    return reader->GetOutput();
}


int main(int argc, char *argv[]){

    if (argc != 3){
	cerr << "usage: " << argv[0] << " <image-1> <image-2> " << endl;
	exit(EXIT_FAILURE); 
    }

    std::string file1 = argv[1];
    std::string file2 = argv[2];
    vtkImageData *image1 = ReadImage(file1);
    //i believe this is reading from png
    int dims1[3];
    image1->GetDimensions(dims1);
    //gets x,y,z dimension info from image
    int npixels1 = dims1[0]*dims1[1];
    vtkImageData *image2 = ReadImage(file2);
    //i believe this is reading from png
    int dims2[3];
    image2->GetDimensions(dims2);
    int npixels2 = dims2[0]*dims2[1];

    if (npixels1 != npixels2){
	cerr << "image 1 has " << npixels1 << " pixels" << endl;
	cerr << "image 2 has " << npixels2 << " pixels" << endl;
	cerr << "these are not the same... " << endl;
	exit(1);
    }
	 
    unsigned char *buffer1 = 
	(unsigned char*)image1->GetScalarPointer(0, 0, 0);
    unsigned char *buffer2 = 
	(unsigned char*)image2->GetScalarPointer(0, 0, 0);

    bool foundDifference = false;
    int numDifferent = 0;

    for (int i = 0; i < npixels1; i++){
	
	if ((buffer1[3*i+0] != buffer2[3*i+0]) ||
	   (buffer1[3*i+0] != buffer2[3*i+0]) ||
	   (buffer1[3*i+0] != buffer2[3*i+0])){

	    numDifferent++;
	    if (numDifferent < 20){
		cerr << "difference at collumn " << i%dims1[0] << ", row ";
		cerr << (i/dims1[0]) << endl;
		cerr << "\tfile 1 " << argv[1] << " has ";
		cerr << (int)buffer1[3*i+0] << ", " << buffer1[3*i+1];
		cerr << ", " << buffer1[3*i+2] << endl;
		cerr << "\tfile 2 " << argv[2] << " has ";
		cerr << (int)buffer2[3*i+0] << ", " << buffer2[3*i+1];
		cerr << ", " << buffer2[3*i+2] << endl;
		}
	    buffer1[3*i+0] = 255;
	    buffer1[3*i+1] = 255;
	    buffer1[3*i+2] = 255;
	}
    }

	cerr << "the number of different pixels is " << numDifferent << endl;

	if (numDifferent > 20){
	    cerr << "only 20 pixels were printed " << endl;
	}
	if (numDifferent == 0){
	    cerr << "wowow no differences here " << endl;
	}
	else{
	    cerr << "writing file differenceMap.png" << endl;
	    WriteImage(image1, "differenceMap");
	}
}
