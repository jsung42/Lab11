#include "wx/wx.h"
#include "wx/sizer.h"

#include "DrawPanel.h"
#include "ImageLoader.h"

#include "Circle.h"
#include "Line.h"
//#include "AVLTree.h"
#include "ListArray.h"
#include "CD.h"
#include "BinarySearchTree.h"
using namespace CSC2110;

#include <iostream>
using namespace std;

class MyApp: public wxApp
{
    bool OnInit();
 
    wxFrame* frame;
    DrawPanel* drawPane;
public:
 
};
 
IMPLEMENT_APP(MyApp)
 
bool MyApp::OnInit()
{
   ListArray<CD>* cds = CD::readCDs("cds.txt");
   int num_items = cds->size();
   cout << num_items << endl;

   ListArrayIterator<CD>* iter = cds->iterator();
   BinarySearchTree<CD>* bst = new BinarySearchTree<CD>(&CD::compare_items, &CD::compare_keys);
   while(iter->hasNext())
   {
      CD* cd = iter->next();
      bst->insert(cd);
   }
   delete iter;
	
   //DO THIS
   //test your tree sort method
   CD** unsorted_cds = cds->toArray();
   CD** sorted_cds = BinarySearchTree<CD>::treeSort(unsorted_cds, num_items, &CD::compare_items, &CD::compare_keys);
   
   //This section of code below is commented to avoid having the screen being clustered up by a ton of outputs. 
   //Also, it shows a completed, unaltered BinarySearchTree tree (after sending it to ToArray and then treeSort) 
   //before testing remove function by removing some title to see if the remove functon is working properly.
   
   /*
   //test to see if the tree sort method has worked by display the sorted list of cds. 
   for(int i = 0; i < num_items; i++)
   {
	   CD* cd = sorted_cds[i];
	   cd->displayCD();
   }
   */

   /*
   //Testing remove function by removing two of the title from the tree.
   String* title = new String("Waiting for the End to Come");
   String* title2 = new String("Wither");
   bst->remove(title);
   bst->remove(title2);
   */
  
   delete cds;
   wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
   frame = new wxFrame((wxFrame *)NULL, -1,  wxT("AVL Tree"), wxPoint(500,500), wxSize(1100,600));
 
   drawPane = new DrawPanel((wxFrame*) frame, bst);
   sizer->Add(drawPane, 1, wxEXPAND);
 
   frame->SetSizer(sizer);
   frame->SetAutoLayout(true);
 
   frame->Show();
   return true;

   return 0;
}