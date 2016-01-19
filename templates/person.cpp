class Person {
public:
  string name;
  int age;
  LList<string> likes;

  Person() {

  }

  Person(string name, int age, LList<string> likes) {
    this->name = name;
    this->age = age;
    this->likes = likes;
  }

  Person(const Person& other) {
    name = other.name;
    age = other.age;
    likes = other.likes;
  }

  Person& operator=(const Person& other) {
    if (&other != this) {
      name = other.name;
      age = other.age;
      likes = other.likes;
    }
    return *this;
  }

  bool operator==(const Person& other) {
    return this->name == other.name;
  }

  bool operator!=(const Person& other) {
    return this->name != other.name;
  }
};

ostream& operator<<(ostream& out, Person& p) {
  out << p.name << " : " << p.age << endl;
  return out;
}
