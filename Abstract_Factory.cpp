#include<iostream>
#include<vector>
#include<algorithm>



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
    int get_power() const;
    virtual std::string Eat(const Herbivore& herbivore) = 0;
 };
int Carnivore::get_power() const
{
    return power;
}

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
    AnimalWorld(Continent* factoryP);
    void MealsHerbivores(std::vector<Herbivore*>& herbivoreP);
    void NutritionCarnivores(std::vector<Carnivore*>& carnivoreP,
                             std::vector<Herbivore*>& herbivoreP);
};
AnimalWorld::AnimalWorld(Continent* factoryP) :factory{ *factoryP } {}
void AnimalWorld::MealsHerbivores(std::vector<Herbivore*>& herbivoreP)
{
    for(auto var : herbivoreP)
        (*var).EatGrass();
}
void AnimalWorld::NutritionCarnivores(std::vector<Carnivore*>& carnivoreP, 
                                      std::vector<Herbivore*>& herbivoreP)
{
    int min1 = carnivoreP.size() < herbivoreP.size() ?
        carnivoreP.size() : herbivoreP.size();

    for (size_t i = 0; i < min1; i++)
    {
        carnivoreP[i]->Eat(*herbivoreP[i]);
    }  
}

void show_weights_herb(std::vector<Herbivore*>& herbP) 
{
    for (auto var : herbP)
        std::cout << (*var).get_weight() << " ";

    std::cout << std::endl;
}
void show_powers_carn(std::vector<Carnivore*>& carnP)
{
    for (auto var : carnP)
        std::cout << (*var).get_power() << " ";

    std::cout << std::endl;
}

int main() {

    std::cout << "Continent: Africa \n";
    std::vector<Herbivore*> herb_animals1;
    Wildebeest w1(50);
    Wildebeest w2(150);
    herb_animals1.push_back(&w1);
    herb_animals1.push_back(&w2);

    std::vector<Carnivore*> carn_animals1;
    Lion l1(50);
    Lion l2(200);
    carn_animals1.push_back(&l1);
    carn_animals1.push_back(&l2);

    std::cout << "Weights of herbivore animals before eating:" << std::endl;
    show_weights_herb(herb_animals1);

    std::cout << "Powers of carnivore animals before eating:" << std::endl;
    show_powers_carn(carn_animals1);

    Africa* afr = new Africa();
    AnimalWorld* aw = new AnimalWorld(afr);
    aw->MealsHerbivores(herb_animals1);
    aw->NutritionCarnivores(carn_animals1, herb_animals1);

    std::cout << "Weights of herbivore animals after eating:" << std::endl;
    show_weights_herb(herb_animals1);

    std::cout << "Powers of carnivore animals after eating:" << std::endl;
    show_powers_carn(carn_animals1);
    
    return 0;
}