/*
    Builder Design Pattern Example in C++

    Purpose:
    The Builder pattern separates the construction of a complex object from its representation,
    allowing the same construction process to create different representations.
    It is useful when an object needs to be created step by step or when the construction process
    must allow different configurations or representations.

    In this example, we build a "Meal" object that can have a main item, a side, and a drink.
    The builder allows us to create different types of meals (e.g., Veg Meal, Non-Veg Meal)
    using the same construction process.
*/

#include <iostream>
#include <string>

// Product
class Meal {
public:
    std::string mainItem;
    std::string sideItem;
    std::string drink;

    void showMeal() const {
        std::cout << "Meal includes: " << mainItem << ", " << sideItem << ", " << drink << std::endl;
    }
};

// Abstract Builder
class MealBuilder {
public:
    virtual ~MealBuilder() {}
    virtual void buildMainItem() = 0;
    virtual void buildSideItem() = 0;
    virtual void buildDrink() = 0;
    virtual Meal* getMeal() = 0;
};

// Concrete Builder 1
class VegMealBuilder : public MealBuilder {
private:
    Meal* meal;
public:
    VegMealBuilder() { meal = new Meal(); }
    ~VegMealBuilder() { delete meal; }
    void buildMainItem() { meal->mainItem = "Veg Burger"; }
    void buildSideItem() { meal->sideItem = "Salad"; }
    void buildDrink() { meal->drink = "Orange Juice"; }
    Meal* getMeal() {
        Meal* finishedMeal = meal;
        meal = nullptr; // Prevent deletion in destructor
        return finishedMeal;
    }
};

// Concrete Builder 2
class NonVegMealBuilder : public MealBuilder {
private:
    Meal* meal;
public:
    NonVegMealBuilder() { meal = new Meal(); }
    ~NonVegMealBuilder() { delete meal; }
    void buildMainItem() { meal->mainItem = "Chicken Burger"; }
    void buildSideItem() { meal->sideItem = "Fries"; }
    void buildDrink() { meal->drink = "Cola"; }
    Meal* getMeal() {
        Meal* finishedMeal = meal;
        meal = nullptr; // Prevent deletion in destructor
        return finishedMeal;
    }
};

// Director
class MealDirector {
public:
    void construct(MealBuilder& builder) {
        builder.buildMainItem();
        builder.buildSideItem();
        builder.buildDrink();
    }
};

int main() {
    MealDirector director;

    VegMealBuilder vegBuilder;
    director.construct(vegBuilder);
    Meal* vegMeal = vegBuilder.getMeal();
    std::cout << "Veg Meal: ";
    vegMeal->showMeal();

    NonVegMealBuilder nonVegBuilder;
    director.construct(nonVegBuilder);
    Meal* nonVegMeal = nonVegBuilder.getMeal();
    std::cout << "Non-Veg Meal: ";
    nonVegMeal->showMeal();

    delete vegMeal;
    delete nonVegMeal;

    return 0;
}