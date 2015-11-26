#include <iostream>
#include "llist.cpp"

using namespace std;

void fillAsQueue(LList<int>& l, int n, int p, int q) {
  while (n) {
    int x;
    cout << ":";
    cin >> x;
    if (p <= x && x <= q) {
      l.ToEnd(x);
      n--;
    }
  }
}

void fillAsStack(LList<int>& l, int n, int p, int q) {
  bool isFirst = true;
  while (n) {
    int x;
    cout << ":";
    cin >> x;
    if (p <= x && x <= q) {
      if (isFirst) {
        isFirst = false;
        l.ToEnd(x);
      } else {
        l.IterStart();
        l.InsertBefore(l.Iter(), x);
      }
      n--;
    }
  }
}

template<typename T>
T LList<T>::operator[](int idx) {
  if (0 > idx || idx >= this->len()) {
    throw "Some sort of error";
  }

  this->IterStart();
  elem<T> * p = this->Iter();
  while (idx) {
    p = (*this).Iter();
    idx--;
  }

  return p->inf;
}

// Problem 1
void readNnumbersBetweenPandQ() {
  LList<int> l;
  int n;
  int p, q;

  cout << "n:";
  cin >> n;
  cout << "[p,q]:";
  cin >> p >> q;

  fillAsQueue(l, n, p, q);
  l.print();
}

// Problem 2
void accessElementByIdx() {
  LList<int> l;
  int n;
  int p, q;

  cout << "n:";
  cin >> n;
  cout << "[p,q]:";
  cin >> p >> q;

  // no elements
  try {
    cout << l[0];
  } catch (const char * x) {
    cout << "Error l[0]: " << x << endl;
  }

  // idx < 0
  try {
    cout << l[-1];
  } catch (const char * x) {
    cout << "Error l[-1]: " << x << endl;
  }

  fillAsQueue(l, n, p, q);
  // idx > len()
  try {
    cout << l[n + 13];
  } catch (const char * x) {
    cout << "Error l[n+13]: " << x << endl;
  }

  // random valid idx
  cout << l[ n / 2] << endl;
}

struct Component {
  const char* name;
  int estimation;

  Component(const char* name, int estimation) {
    this->name = name;
    this->estimation = estimation;
  }
};

struct Feature {
  const char* name;
  LList<Component*> * components;

  Feature(const char* name) {
    this->name = name;
    components = new LList<Component*>();
  }

  void add(Component * c) {
    this->components->ToEnd(c);
  }

  ~Feature() {
    delete components;
  }
};

/*
  Feature {
    char* name;
    LList<Component>* components
      name,
      est
  }

  // features
   // fb login
      // front-end: 2
      // back-end: 2
      // testing: 1
   // list of friends
      // front-end: 1
      // back-end: 3
      // testing: 2
   // send email
      // back-end: 1
      // testing: 1
ConverTo
  // front-end, 3
    // fb login, 2
    // list of friends, 1
*/
void printFeatures(LList<Feature*>& features) {
  features.IterStart();
  elem<Feature*> * p = features.Iter();
  while (p) {
    cout << p->inf->name << endl;
    LList<Component*> * components = p->inf->components;

    components->IterStart();
    elem<Component*> * q = components->Iter();
    while (q) {
      cout << "  " << q->inf->name << "(" << q->inf->estimation << ")" << endl;
      q = components->Iter();
    }
    p = features.Iter();
  }
}

int estimationForComponent(LList<Feature*>& features, const char * componentName) {
  int componentEstimation = 0;

  features.IterStart();
  elem<Feature*> * p = features.Iter();
  while (p) {
    LList<Component*> * components = p->inf->components;

    components->IterStart();
    elem<Component*> * q = components->Iter();
    while (q) {
      if (strcmp(q->inf->name, componentName) == 0) {
        componentEstimation+= q->inf->estimation;
      }
      q = components->Iter();
    }
    p = features.Iter();
  }
  return componentEstimation;
}

void addIfNotExists(LList<const char *>& components, const char* name) {
  components.IterStart();
  elem<const char*> * p = components.Iter();
  while (p) {
    if (strcmp(p->inf, name) == 0) {
      return;
    }
    p = components.Iter();
  }
  components.ToEnd(name);
}

LList<const char*> allComponents(LList<Feature*>& features) {
  LList<const char *> allComponents;

  features.IterStart();
  elem<Feature*> * p = features.Iter();
  while (p) {
    LList<Component*> * components = p->inf->components;

    components->IterStart();
    elem<Component*> * q = components->Iter();
    while (q) {
      addIfNotExists(allComponents, q->inf->name);
      q = components->Iter();
    }
    p = features.Iter();
  }
  return allComponents;
}

int main() {
  Feature* feature1 = new Feature("FB login");
  feature1->add(new Component("front-end", 2));
  feature1->add(new Component("back-end", 2));
  feature1->add(new Component("testing", 1));

  Feature* feature2 = new Feature("List of friends");
  feature2->add(new Component("front-end", 1));
  feature2->add(new Component("back-end", 3));
  feature2->add(new Component("testing", 2));

  Feature* feature3 = new Feature("Send email");
  feature3->add(new Component("back-end", 1));
  feature3->add(new Component("testing", 1));

  LList<Feature*> features;
  features.ToEnd(feature1);
  features.ToEnd(feature2);
  features.ToEnd(feature3);

  printFeatures(features);
  cout << "front-end estimation is: "
       << estimationForComponent(features, "front-end")
       << endl;

  LList<const char*> components = allComponents(features);
  components.print();

  components.IterStart();
  elem<const char *> * p = components.Iter();
  while (p) {
    cout << p->inf
         << ": "
         << estimationForComponent(features, p->inf)
         << endl;
    p = components.Iter();
  }

  return 0;
}
