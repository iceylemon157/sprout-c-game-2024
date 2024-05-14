enum Ingredient {
    // Non-edible
    Plate,

    // Raw Ingredients
    Cabbage,
    Cheese,
    MeatPatty,
    Tomato,

    // Processed Ingredients
    Bread,
    SlicedCabage,
    SlicedCheese,
    SlicedTomato,
    CookedPatty,

    // Overcooked Ingredients
    BurntPatty,
};

enum Recipe {
    Salad,
    Burger,
    CheeseBurger,
    MegaBurger,
};

enum FryingState {
    Idle,
    Frying,
    Fried,
    Burnt,
};

enum DeliveryState {
    // Is this necessary?
    // Idle,
    Delivered,
    Failed,
};

enum Counter {
    // Ingredient counters
    BreadCounter,
    CabbageCounter,
    CheeseCounter,
    MeatPattyCounter,
    TomatoCounter,

    // Tool counters
    CuttingCounter,
    StoveCounter,
    NormalCounter,
    PlatesCounter,
    TrashCounter,
    DeliveryCounter,
};

enum Event {
    // Global events
    Round,
    TotalScore,
    TimeLeft,

    // Recipe events
    NewRecipe,
    RecipeList, // with score change and time left

    // Should the following two be replaced with DeliveryState?
    RecipeDelivered,
    RecipeTimeout,
    
    // Player events
    PlayerPosition,
    PlayerHoldItems,

    // Ingredient events
    FryingTimer,
    FryingState,

};
