/*==============================================================================

  Program: 3D Slicer

  Copyright (c) Kitware Inc.

  See COPYRIGHT.txt
  or http://www.slicer.org/copyright/copyright.txt for details.

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

  This file was originally developed by Julien Finet, Kitware Inc.
  and was partially funded by NIH grant 3P41RR013218-12S1

==============================================================================*/

// MRML includes
#include "vtkMRMLCoreTestingMacros.h"
#include "vtkMRMLVolumeNode.h"

// VTK includes
#include <vtkImageData.h>
#include <vtkNew.h>

//---------------------------------------------------------------------------
class vtkMRMLTestVolumeNode
  : public vtkMRMLVolumeNode
{
public:
  static vtkMRMLTestVolumeNode *New(){return new vtkMRMLTestVolumeNode;}
  virtual vtkMRMLNode* CreateNodeInstance(){return new vtkMRMLTestVolumeNode;}
  virtual const char* GetNodeTagName(){return "vtkMRMLTestVolumeNode";}
  vtkMRMLTestVolumeNode(){}
};

//---------------------------------------------------------------------------
int vtkMRMLVolumeNodeEventsTest(int , char * [] )
{
  vtkNew< vtkMRMLTestVolumeNode > volumeNode;

  vtkNew<vtkMRMLNodeCallback> callback;

  volumeNode->AddObserver(vtkCommand::AnyEvent, callback.GetPointer());

  // Test vtkMRMLVolumeNode::SetAndObserveImageData()
  vtkNew<vtkImageData> imageData;
  volumeNode->SetAndObserveImageData(imageData.GetPointer());

  if (!callback->GetErrorString().empty() ||
      callback->GetNumberOfEvents(vtkCommand::ModifiedEvent) != 1 ||
      callback->GetNumberOfEvents(vtkMRMLVolumeNode::ImageDataModifiedEvent) != 1)
    {
    std::cerr << __LINE__ << ": vtkMRMLVolumeNode::SetAndObserveImageData failed: "
              << callback->GetErrorString().c_str() << " "
              << "Number of ModifiedEvent: "
              << callback->GetNumberOfEvents(vtkCommand::ModifiedEvent) << " "
              << "Number of ImageDataModifiedEvent: "
              << callback->GetNumberOfEvents(vtkMRMLVolumeNode::ImageDataModifiedEvent)
              << std::endl;
    return EXIT_FAILURE;
    }
  callback->ResetNumberOfEvents();

  // Set the same image data:
  volumeNode->SetAndObserveImageData(imageData.GetPointer());
  if (!callback->GetErrorString().empty() ||
      callback->GetNumberOfEvents(vtkCommand::ModifiedEvent) != 0 ||
      callback->GetNumberOfEvents(vtkMRMLVolumeNode::ImageDataModifiedEvent) != 0)
    {
    std::cerr << __LINE__ << ": vtkMRMLVolumeNode::SetAndObserveImageData failed: "
              << callback->GetErrorString().c_str() << " "
              << "Number of ModifiedEvent: "
              << callback->GetNumberOfEvents(vtkCommand::ModifiedEvent) << " "
              << "Number of ImageDataModifiedEvent: "
              << callback->GetNumberOfEvents(vtkMRMLVolumeNode::ImageDataModifiedEvent)
              << std::endl;
    return EXIT_FAILURE;
    }
  callback->ResetNumberOfEvents();

  // Update image data
  imageData->Modified();
  if (!callback->GetErrorString().empty() ||
      callback->GetNumberOfEvents(vtkCommand::ModifiedEvent) != 0 ||
      callback->GetNumberOfEvents(vtkMRMLVolumeNode::ImageDataModifiedEvent) != 1)
    {
    std::cerr << "vtkImageData::Modified failed."
              << callback->GetErrorString().c_str() << " "
              << "Number of ModifiedEvent: "
              << callback->GetNumberOfEvents(vtkCommand::ModifiedEvent) << " "
              << "Number of ImageDataModifiedEvent: "
              << callback->GetNumberOfEvents(vtkMRMLVolumeNode::ImageDataModifiedEvent)
              << std::endl;
    return EXIT_FAILURE;
    }
  callback->ResetNumberOfEvents();

  // Update volume node
  volumeNode->Modified();
  if (!callback->GetErrorString().empty() ||
      callback->GetNumberOfEvents(vtkCommand::ModifiedEvent) != 1 ||
      callback->GetNumberOfEvents(vtkMRMLVolumeNode::ImageDataModifiedEvent) != 0)
    {
    std::cerr << __LINE__ << ": vtkMRMLVolumeNode::Modified failed: "
              << callback->GetErrorString().c_str() << " "
              << "Number of ModifiedEvent: "
              << callback->GetNumberOfEvents(vtkCommand::ModifiedEvent) << " "
              << "Number of ImageDataModifiedEvent: "
              << callback->GetNumberOfEvents(vtkMRMLVolumeNode::ImageDataModifiedEvent)
              << std::endl;
    return EXIT_FAILURE;
    }
  callback->ResetNumberOfEvents();

  // Set new image data
  vtkNew<vtkImageData> imageData2;
  volumeNode->SetAndObserveImageData(imageData2.GetPointer());

  if (!callback->GetErrorString().empty() ||
      callback->GetNumberOfEvents(vtkCommand::ModifiedEvent) != 1 ||
      callback->GetNumberOfEvents(vtkMRMLVolumeNode::ImageDataModifiedEvent) != 1)
    {
    std::cerr << __LINE__ << ": vtkMRMLVolumeNode::SetAndObserveImageData failed: "
              << callback->GetErrorString().c_str() << " "
              << "Number of ModifiedEvent: "
              << callback->GetNumberOfEvents(vtkCommand::ModifiedEvent) << " "
              << "Number of ImageDataModifiedEvent: "
              << callback->GetNumberOfEvents(vtkMRMLVolumeNode::ImageDataModifiedEvent)
              << std::endl;
    return EXIT_FAILURE;
    }
  callback->ResetNumberOfEvents();

  // Update old image data
  imageData->Modified();

  if (!callback->GetErrorString().empty() ||
      callback->GetNumberOfEvents(vtkCommand::ModifiedEvent) != 0 ||
      callback->GetNumberOfEvents(vtkMRMLVolumeNode::ImageDataModifiedEvent) != 0)
    {
    std::cerr << __LINE__ << ": vtkMRMLVolumeNode::SetAndObserveImageData failed: "
              << callback->GetErrorString().c_str() << " "
              << "Number of ModifiedEvent: "
              << callback->GetNumberOfEvents(vtkCommand::ModifiedEvent) << " "
              << "Number of ImageDataModifiedEvent: "
              << callback->GetNumberOfEvents(vtkMRMLVolumeNode::ImageDataModifiedEvent)
              << std::endl;
    return EXIT_FAILURE;
    }
  callback->ResetNumberOfEvents();

  // Update new image data
  imageData2->Modified();

  if (!callback->GetErrorString().empty() ||
      callback->GetNumberOfEvents(vtkCommand::ModifiedEvent) != 0 ||
      callback->GetNumberOfEvents(vtkMRMLVolumeNode::ImageDataModifiedEvent) != 1)
    {
    std::cerr << __LINE__ << ": vtkMRMLVolumeNode::SetAndObserveImageData failed: "
              << callback->GetErrorString().c_str() << " "
              << "Number of ModifiedEvent: "
              << callback->GetNumberOfEvents(vtkCommand::ModifiedEvent) << " "
              << "Number of ImageDataModifiedEvent: "
              << callback->GetNumberOfEvents(vtkMRMLVolumeNode::ImageDataModifiedEvent)
              << std::endl;
    return EXIT_FAILURE;
    }
  callback->ResetNumberOfEvents();

  // Clear image data
  volumeNode->SetAndObserveImageData(0);

  if (!callback->GetErrorString().empty() ||
      callback->GetNumberOfEvents(vtkCommand::ModifiedEvent) != 1 ||
      callback->GetNumberOfEvents(vtkMRMLVolumeNode::ImageDataModifiedEvent) != 1)
    {
    std::cerr << __LINE__ << ": vtkMRMLVolumeNode::SetAndObserveImageData failed: "
              << callback->GetErrorString().c_str() << " "
              << "Number of ModifiedEvent: "
              << callback->GetNumberOfEvents(vtkCommand::ModifiedEvent) << " "
              << "Number of ImageDataModifiedEvent: "
              << callback->GetNumberOfEvents(vtkMRMLVolumeNode::ImageDataModifiedEvent)
              << std::endl;
    return EXIT_FAILURE;
    }
  callback->ResetNumberOfEvents();

  return EXIT_SUCCESS;
}
