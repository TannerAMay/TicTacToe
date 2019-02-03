#include "../multitree.h"

int main()
{
  MultiTree m0;

  m0.addNode(coords(1, 1), 1);
  m0.move(coords(1, 1), 1);
  m0.at()->boardStr = "1--------";

  m0.addNode(coords(2, 2), 2);
  m0.addNode(coords(2, 2), 2.1);
  m0.move(coords(2, 2), 2);
  m0.at()->boardStr = "-1-------";

  m0.addNode(coords(3, 3), 3);
  m0.addNode(coords(3, 3), 3.1);
  m0.addNode(coords(3, 3), 3.2);

  m0.move(coords(3, 3), 3);
  m0.at()->boardStr = "--1------";
  m0.moveUp();

  m0.move(coords(3, 3), 3.1);
  m0.at()->boardStr = "--1------";
  m0.moveUp();

  m0.move(coords(3, 3), 3.2);
  m0.at()->boardStr = "--1------";
  m0.moveUp();

  m0.moveUp();
  m0.move(coords(2, 2), 2.1);
  m0.at()->boardStr = "-1-------";

  m0.addNode(coords(3, 4), 3);
  m0.addNode(coords(3, 4), 3.1);
  m0.addNode(coords(3, 4), 3.2);

  m0.move(coords(3, 4), 3);
  m0.at()->boardStr = "--1------";
  m0.moveUp();

  m0.move(coords(3, 4), 3.1);
  m0.at()->boardStr = "--1------";
  m0.moveUp();

  m0.move(coords(3, 4), 3.2);
  m0.at()->boardStr = "--1------";
  m0.moveUp();

  m0.print();

  m0.popRoot(0);

  m0.print();

  /*//cout << "Just one:\n";
  coords l0(1, 1);
  m0.addNode(l0, 1);
  //m0.print();

  //cout << "\n\nMany:\n";
  coords l1(2, 2);
  coords l2(3, 3);
  coords l3(4, 4);
  coords l4(5, 5);
  m0.addNode(l1, 2);
  m0.addNode(l2, 3);
  m0.addNode(l3, 4);
  m0.addNode(l4, 5);
  //m0.print();

  //cout << "\n\nMove(int):\n";
  m0.move(2);
  coords ind2loc0(20, 20);
  coords ind2loc1(21, 21);
  coords ind2loc2(22, 22);
  coords ind2loc3(23, 23);
  m0.addNode(ind2loc0, 20);
  m0.addNode(ind2loc1, 21);
  m0.addNode(ind2loc2, 22);
  m0.addNode(ind2loc3, 23);
  //m0.print();

  //cout << "\n\nMove(node):\n";
  coords moveRC(20, 20);
  node moveNode(moveRC, 20);
  m0.move(moveNode);
  coords child3ind0loc0(300, 300);
  coords child3ind0loc1(301, 301);
  coords child3ind0loc2(302, 302);
  coords child3ind0loc3(303, 303);
  m0.addNode(child3ind0loc0, 300);
  m0.addNode(child3ind0loc1, 301);
  m0.addNode(child3ind0loc2, 302);
  m0.addNode(child3ind0loc3, 303);
  //m0.print();

  //cout << "\n\nMove(coords, int):\n";
  coords moveRC2(302, 302);
  m0.move(moveRC2, 302);
  coords child4ind3loc0(430, 430);
  coords child4ind3loc1(431, 431);
  coords child4ind3loc2(432, 432);
  coords child4ind3loc3(433, 433);
  m0.addNode(child4ind3loc0, 430);
  m0.addNode(child4ind3loc1, 431);
  m0.addNode(child4ind3loc2, 432);
  m0.addNode(child4ind3loc3, 433);
  //m0.print();


  m0.exp();

  return 0;*/
}
