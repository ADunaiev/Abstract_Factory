#include<iostream>


class Herbivore {
protected:
    int weight;
    bool life;
public:
    virtual ~Herbivore() {};
    int get_weight() const { return weight; }
    virtual std::string EatGrass() = 0;
};

class Wildebeest : public Herbivore {

public:
    Wildebeest(int weightP);
    Wildebeest();
    std::string EatGrass() override;
};
Wildebeest::Wildebeest(int weightP)  
{
    weight = weightP;
    life = 1;
}
Wildebeest::Wildebeest():Wildebeest(100){}
std::string Wildebeest::EatGrass()
{
    weight += 10;
    return "Wildebeest is eating grass.";
}

class Bison : public Herbivore {
public:
    Bison(int weightP);
    Bison();
    std::string EatGrass() override;
};
Bison::Bison(int weightP)
{
    weight = weightP;
    life = 1;
}
Bison::Bison():Bison(100){}
std::string Bison::EatGrass()
{
    weight += 10;
    return "Bison is eating grass.";
}


class Carnivore {
protected:
    int power;

public:
    virtual ~Carnivore() {};
    virtual std::string Eat(const Herbivore& herbivore) = 0;
 };

class Lion : public Carnivore{
public:
    Lion(int powerP);
    Lion();
    std::string Eat(const Herbivore& herbovore) override;
};
Lion::Lion(int powerP)
{
    power = powerP;
}
Lion::Lion() :Lion(110){}
std::string Lion::Eat(const Herbivore& herbivore) {

    if (power > herbivore.get_weight())
        power += 10;
    else
        power -= 10;

    return "Lion is eating";
}

class Wolf : public Carnivore {
public:
    Wolf(int powerP);
    Wolf();
    std::string Eat(const Herbivore& herbovore) override;
};
Wolf::Wolf(int powerP)
{
    power = powerP;
}
Wolf::Wolf() :Wolf(90) {}
std::string Wolf::Eat(const Herbivore& herbivore) {

    if (power > herbivore.get_weight())
        power += 10;
    else
        power -= 10;

    return "Wolf is eating";
}

class Continent {
public:
    virtual Herbivore* CreateHerbivore() const = 0;
    virtual Carnivore* CreateCarnivore() const = 0;
};

class Africa : public Continent {
public:
    Herbivore* CreateHerbivore() const override {
        return new Wildebeest();
    }
    Carnivore* CreateCarnivore() const override {
        return new Lion();
    }
};

class NorthAmerica : public Continent {
public:
    Herbivore* CreateHerbivore() const override {
        return new Bison();
    }
    Carnivore* CreateCarnivore() const override {
        return new Wolf();
    }
};


class AnimalWorld
{

    Continent& factory;
public:
    AnimalWorld(Continent& factoryP);
    void MealsHerbivores(Herbivore* herbivoreP);
    void NutritionCarnivores(Carnivore* carnivoreP,)

};
AnimalWorld::AnimalWorld(Continent& factoryP) :factory{ factoryP } {}


int main() {
    //std::cout << "Client: Testing client code with the first factory type:\n";
    //Africa* f1 = new Africa();
    //AnimalWorld(*f1);
    //delete f1;
    //std::cout << std::endl;
    //std::cout << "Client: Testing the same client code with the second factory type:\n";
    //NorthAmerica* f2 = new NorthAmerica();
    //AnimalWorld(*f2);
    //delete f2;
    return 0;
}