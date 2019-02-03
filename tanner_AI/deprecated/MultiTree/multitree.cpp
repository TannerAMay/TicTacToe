#include "multitree.h"

void MultiTree::remove(node *&rt)
{
  if(rt == nullptr)
    return;

  int size = rt->children.size();

  for(int index = 0; index < size; index++)
    remove(rt->children.at(index));

  delete rt;
  rt = nullptr;
}

void MultiTree::printRecurse(node *rt, string indent)
{
  if(rt == nullptr)
  {
    cout << indent << "   empty" << endl;
  }
  else
  {
    int size = rt->children.size();
    int index = size - 1;

    for(; index >= size / 2 || index == 0; index--)
        printRecurse(rt->children.at(index), indent + "  ");

    //if(index == -1)
    //  index++;

    cout << indent << rt->boardStr << " (" << rt->loc.row << ", "
         << rt->loc.col << ") " << rt->eval << endl;

    for(; index >= 0; index--)
      printRecurse(rt->children.at(index), indent + "  ");

    if(index == -1)
      cout << indent << "     empty" << endl;
  }

}

void MultiTree::expRecurse(node *rt)
{
  if(rt->children[0] == nullptr)
  {
    cout << rt->boardStr << " " << rt->loc.row << "," << rt->loc.col
         << ":" << rt->eval << " " << "0\n";
  }
  else
  {
    int sz = rt->children.size();

    cout << rt->boardStr << " " << rt->loc.row << ","
         << rt->loc.col << ":" << rt->eval << " " << sz << endl;

    for(int i = 0; i < sz; i++)
    {
      expRecurse(rt->children.at(i));
    }
  }
}

MultiTree::~MultiTree()
{
  remove(root);
}

void MultiTree::print()
{
  printRecurse(root, "");
}

void MultiTree::addNode(const coords &loc, const float &eval)
{
  if(curr->children.front() == nullptr)
    curr->children.front() = new node(loc, eval, curr);
  else
  {
    curr->children.push_back(new node(loc, eval, curr));
    curr->children.back()->parent = curr;
  }
}

void MultiTree::popRoot(node *switchTo)
{
  if(root == nullptr)
    return;

  int size = root->children.size();

  for(int index = size - 1; index > 0; index--)
  {
    if(root->children.at(index) == switchTo)
    {
      std::iter_swap(root->children.begin() + 0,
                     root->children.begin() + index);
    }

    remove(root->children[index]);
    curr = root->children.front();
    //delete root;
  }


}

void MultiTree::popRoot(int index)
{
  if(root == nullptr)
    return;

  //int size = root->children.size();

  std::iter_swap(root->children.begin() + 0,
                 root->children.begin() + index);

  remove(root);
  curr = root->children.front();
  delete root;
}

void MultiTree::move(int index)
{
  if(index > curr->children.size())
    throw std::out_of_range("Move \"curr\" failed.");

  curr = curr->children.at(index);
}

void MultiTree::move(node *index)
{
  int size = curr->children.size();

  for(int i = 0; i < size; i++)
  {
    if(curr->children.at(i)->loc == index->loc
       && (abs(curr->children.at(i)->eval - index->eval) < abs(curr->children.at(i)->eval) * 0.00001))//(curr->children.at(i)->eval == index->eval))//(abs(curr->children.at(i)->eval - index->eval) < abs(curr->children.at(i)->eval) * 0.00001))
    {
      curr = curr->children.at(i);
      return;
    }
  }
}

void MultiTree::move(coords index, float val)
{
  int size = curr->children.size();

  for(int i = 0; i < size; i++)
  {
    if(curr->children.at(i)->loc == index
       && (abs(curr->children.at(i)->eval - val) < abs(curr->children.at(i)->eval) * 0.00001))
    {
      curr = curr->children.at(i);
      return;
    }
  }
}

void MultiTree::moveUp()
{
  if(curr->parent != nullptr)
    curr = curr->parent;
}

void MultiTree::impRecurse(std::ifstream &file)
{
  string str = "";
  getline(file, str);
  int strLen = str.length();
  int index = 0;
  //--------- r,c:s chil

  string bStr = "";
  for(; index < strLen && index < 9; index++) //read in boardStr
  {
    bStr.push_back(str[index]);
  }
  if(index >= strLen)
     throw "Index is out of range.";
  // r,c:s chil
  index++;
  //r,c:s chil

  string r = "";
  for(; index < strLen && str[index] != ','; index++) //read in row
  {
    r.push_back(str[index]);
  }
  if(index >= strLen)
     throw "Index is out of range. 1";
  //,c:s chil
  index++;
  //c:s chil

  string c = "";
  for(; index < strLen && str[index] != ':'; index++) //read in col
  {
    c.push_back(str[index]);
  }
  if(index >= strLen)
     throw "Index is out of range. 2";
  //:s chil
  index++;
  //s chil

  //s is float
  string s = "";
  for(; index < strLen && str[index] != ' '; index++) //read in score
  {
    s.push_back(str[index]);
  }
  if(index >= strLen)
     throw "Index is out of range. 3";
  // chil
  index++;
  //chil

  string chil = "";
  for(; index < strLen; index++) //read in number of children
  {
    chil.push_back(str[index]);
  }
  int numChild = stoi(chil);

  if(curr->boardStr != "---------") //if not root
  {
    addNode(coords(std::stoi(r, nullptr), std::stoi(c, nullptr)), std::stof(s, nullptr));
    curr->children.back()->boardStr = bStr;
  }
  //root already set up in class

  for(; numChild > 0; numChild--)
  {
    move(curr->children.back());
    impRecurse(file);
    moveUp();
  }

  return;
}

void MultiTree::imp()
{
  std::ifstream tree("../treebuilder/treegen.txt");

  if(tree.is_open())
  {
    impRecurse(tree);
  }
  else
  {
    throw "File could not be opened.";
  }
}
