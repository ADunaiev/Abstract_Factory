#include<iostream>
#include<vector>

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

class Elk : public Herbivore {
public:
    Elk(int weightP);
    Elk();
    std::string EatGrass() override;
};
Elk::Elk(int weightP)
{
    weight = weightP;
    life = 1;
}
Elk::Elk() : Elk(100) {}
std::string Elk::EatGrass()
{
    weight += 10;
    return "Elk is eating grass.";
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

class Tiger : public Carnivore {
public:
    Tiger(int powerP);
    Tiger();
    std::string Eat(const Herbivore& herbovore) override;
};
Tiger::Tiger(int powerP)
{
    power = powerP;
}
Tiger::Tiger() : Tiger(90) {}
std::string Tiger::Eat(const Herbivore& herbivore) {

    if (power > herbivore.get_weight())
        power += 10;
    else
        power -= 10;

    return "Tiger is eating";
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
class Eurasia : public Continent {
public:
    Herbivore* CreateHerbivore() const override {
        return new Elk();
    }
    Carnivore* CreateCarnivore() const override {
        return new Tiger();
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

    std::cout << "\nContinent: North America \n";
    std::vector<Herbivore*> herb_animals2;
    Bison b1(50);
    Bison b2(150);
    Bison b3;
    herb_animals2.push_back(&b1);
    herb_animals2.push_back(&b2);
    herb_animals2.push_back(&b3);

    std::vector<Carnivore*> carn_animals2;
    Wolf wo1(50);
    Wolf wo2(200);
    carn_animals2.push_back(&wo1);
    carn_animals2.push_back(&wo2);

    std::cout << "Weights of herbivore animals before eating:" << std::endl;
    show_weights_herb(herb_animals2);

    std::cout << "Powers of carnivore animals before eating:" << std::endl;
    show_powers_carn(carn_animals2);

    NorthAmerica* n_am = new NorthAmerica();
    AnimalWorld* aw2 = new AnimalWorld(n_am);
    aw2->MealsHerbivores(herb_animals2);
    aw2->NutritionCarnivores(carn_animals2, herb_animals2);

    std::cout << "Weights of herbivore animals after eating:" << std::endl;
    show_weights_herb(herb_animals2);

    std::cout << "Powers of carnivore animals after eating:" << std::endl;
    show_powers_carn(carn_animals2);

    std::cout << "\nContinent: Eurasia \n";
    std::vector<Herbivore*> herb_animals3;
    Elk e1(50);
    Elk e2(150);
    herb_animals3.push_back(&e1);
    herb_animals3.push_back(&e2);

    std::vector<Carnivore*> carn_animals3;
    Tiger t1(50);
    Tiger t2(200);
    Tiger t3;
    carn_animals3.push_back(&t1);
    carn_animals3.push_back(&t2);
    carn_animals3.push_back(&t3);

    std::cout << "Weights of herbivore animals before eating:" << std::endl;
    show_weights_herb(herb_animals3);

    std::cout << "Powers of carnivore animals before eating:" << std::endl;
    show_powers_carn(carn_animals3);

    Eurasia* eur = new Eurasia();
    AnimalWorld* aw3 = new AnimalWorld(eur);
    aw3->MealsHerbivores(herb_animals3);
    aw3->NutritionCarnivores(carn_animals3, herb_animals3);

    std::cout << "Weights of herbivore animals after eating:" << std::endl;
    show_weights_herb(herb_animals3);

    std::cout << "Powers of carnivore animals after eating:" << std::endl;
    show_powers_carn(carn_animals3);
    
    return 0;
}