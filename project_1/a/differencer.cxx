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
    int npixels = 
