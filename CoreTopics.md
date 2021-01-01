# Core Topics

## Pointers + Arrays

  * Pointer is a variable type which stores memory address. When we declare pointer, we need data type and the name of pointer. Array is the data structure which can store elements which are made up of same data types. We need data type, name of array and number of elements in array when we declare array. There are several reasons why arrays and pointers are important. Pointer also have few important meanings. First, by using pointer, we can show up more than one value. For example, we can point at that start of the array so that we can point whole array by pointing only one place. Also, pointer is more efficient to handle data types. Array is important because we can keep track of many variables easily which is hard if we declare all of them as individual variable. Every byte in memory is identifiable by its location. We identify their location by using bites which is address of the memory. In the pointer data type, we store this address by using virtual memory. Array is the group of values which stored in memory in a row by having consistant chunk of memory location.

  ```c++
    private:
        ItemType       itemType = ItemType::NOTHING;
        ObjectManager* objectManager;
  ```
  ```c++
    if (isCollideWithPlayer() == true)
    {
        objectManager->GetPlayer()->GetItem(itemType);
        objectManager->Destroy(id);
    }
  ```


## Bit operations

  * This is operation which calculates against a single or two binary numbers at the each digits of those numbers. This is important because bitwise operations are super simple so that we can run program faster than using arithmetic calculation

  Operator | Work
  ---------|-------
  & | And operator whose result become 1 if both bits are 1
  &#124; | Or operator whose result become 1 if any of bits are 1
  ^ | XOR operator whose result become 1 if two bits are different
  << | Left shift operator which moves the bits to the left
  &#62;&#62; | Right shift operator which moves the bits to the right
  ~ | Not operator which takes one binary number and convert it

  ```c++
  constexpr int DAMAGE = 4;
  constexpr int MOVE = 2;
  constexpr int ATTACK = 1;
  ```

  ```c++
  if ((state & MOVE) == MOVE)
  {
  	  set_fill_color(Color{ 0, 255, 0, 255 });
  }
  else
  {
      set_fill_color(Color{ 0, 0, 0, 255 });
  }
  ```

  ```c++
  double dx = mouseX - x + (rand() & 0x15) - (rand() & 0x15);
  double dy = mouseY - y + (rand() & 0x15) - (rand() & 0x15);
  ```


## Operator Overloading

  * Operator overloading is a function which gave special work to operator for a data type. There are several importance of operator overloading. First, it allows programmers to have user defined meanings into class. For example, arithmetic operations are only for numbers. If we use this when it is not suitable, it will cause an error. However, by using operator overloading, programmers can put meaning with those marks and able to use it. Also, programmers can put meanings for intuitive operators so that it will make code easier to interpret. This works when we call overloaded function or operator, compiler try to find which definition is the best for that situation. By defining operator overloading, compiler choose the best operator as programmers' custom operator.

## Return Value Optimization

  * There are two kinds of return value optimization (so called as RVO). First one is named RVO. When function is return by variable, it is called as named RVO. However, if there are several return setences in that function, all return variable should be same variable. The other thing is unnamed RVO. If programmer just call constructor at the return setence, it becomes unnamed RVO. We can save time by using this during run time and we can reduce lots of time especially when it comes to dealing with lots of memories. Instead of doing deep copy in the code, call constructor right away so that it does not do deep copy and put value into return memory right away.

  ```c++
  double Player::ShortestDistanceSqr(double circleX, double circleY, double onesideX, double onesideY, double theotherX, double theotherY)
  {
      double distanceSqr;

      //Vector between point p and the start point of the edge 
      double minusRPX = circleX - onesideX;
      double minusRPY = circleY - onesideY;
      //Vector between start point of the edge and end point of the edge
      double minusQPX = theotherX - onesideX;
      double minusQPY = theotherY - onesideY;
      //Vector between point p and the end point of the edge
      double minusRQX = circleX - theotherX;
      double minusRQY = circleY - theotherY;

      //distance between line and the point
      if ((minusRPX * minusQPX + minusRPY * minusQPY) < 0) //When edgeStart is the closest point on line to point R
      {
          distanceSqr = minusRPX * minusRPX + minusRPY * minusRPY;
      }
      //When edgeEnd is the closest point on line to point R
      else if ((minusRPX * minusQPX + minusRPY * minusQPY) > (minusQPX * minusQPX + minusQPY * minusQPY))
      {
          distanceSqr = minusRQX * minusRQX + minusRQY * minusRQY;
      }
      //When closest point from point R is on the edge
      else
      {
          distanceSqr = (minusRPX * minusRPX + minusRPY * minusRPY) 
            - ((minusRPX * minusQPX + minusRPY * minusQPY) * (minusRPX * minusQPX + minusRPY * minusQPY))
            / (minusQPX * minusQPX + minusQPY * minusQPY);
      }

      return distanceSqr;
  }
  ```

## Inheritance + Polymorphism

  * Inheritance is that takes all data from the superclass and make it able to use them in subclass. Polymorphism means which helps inherited methods distinguishable and perform different task. This is important because of resuability. We can reuse existing class functions by using this. These works with these steps. First, compiler makes virtual table. There is ambiguous situation when we use inheritance which means we need polymorphism. At that time, system check virtual table and call the funtion from the table of that class. When same name function is overrided in the subclass, then we cannot call the same name function from base class.

  ```c++
  class Player : public Object
  {
  public:
      Player() = default;
      Player(double positionX, double positionY, double speedX, double speedY, double width, double height, DrawType drawType);
      Player(double positionX, double positionY, double speedX, double speedY, double width, double height, const std::filesystem::path& imagePath);
      void Update() override;
      void Draw() override;

      void Move(Direction direction);
      void GunShot();
    ```

  ```c++
  class Object
  {
  public:
      Object() = default;
      Object(double positionX, double positionY, double speedX, double speedY, double width, double height, DrawType drawType);
      Object(double positionX, double positionY, double speedX, double speedY, double width, double height, const std::filesystem::path& imagePath);
      Object(const Object& rhs) = default;
      Object(Object&& rhs) = default;

      virtual ~Object() = default;
      virtual void Update();
      virtual void Draw();
  
      Object& operator=(const Object& rhs) = default;
      Object& operator=(Object&& rhs) = default;

  ```
## Rule of 5, RAII, r-value reference / Move Semantics

  * What is this?
  	* Rule of 5: This case is called as rule of 5 if class contains destructor, copy constructor, copy assignment operator, move constructor and move assignment operator.
  	* RAII: When we try to run code outside of field where our variable is used, this pattern helps us delete that variable automatically so that we don't have to care more.
  	* r-value reference: We can reference r values by using r-value reference which was impossible before as reference is only for l value
  	* Move Semantics: Instead of deep copy the r value which occurs extra use of memory, do shallow copy instead so that we can save time and memory

  * Why is this important?
    * If we do not implement rule of 5, compiler make rule of 5 automatically. However, there is a possibility that it will work different with what we intended so we have to make our own rule of 5 to prevent that situation.
  	* RAII is important because we do not have to care about destruction everytime once we set it as RAII pattern.
    * By using r-value reference and move semantic, we can reduce time during runtime especially if there are lots of data to copy.

  * How does it work?
  	* Rule of 5: Just declare destructor, copy constructor, copy assignment operator, move constructor and move assignment operator in the same class
  	* RAII: unique_ptr / catch & throw (Instead of making destructor, make memory delete everything what we allocated so that we don't have to care about memory leak)
  	* r-value reference / Move Semantics: When this happens, they does not do deep copy while it is proceeding. Instead, move their pointers so that result will be swap address of each variables

  ```c++
  class ParticleSystem
  {
  public:
      ParticleSystem() = default;
      ParticleSystem(double positionX, double positionY, double speedX, double speedY, double lifeTime,
                   int particleAmount);
      ~ParticleSystem();

      ParticleSystem(const ParticleSystem& rhs);
      ParticleSystem(ParticleSystem&& rhs) noexcept;

      ParticleSystem& operator=(const ParticleSystem& rhs);
      ParticleSystem& operator=(ParticleSystem&& rhs) noexcept;

      void Draw();

  private:
      Particle* particles;
      int       totalParticles;
  };
  ```

  ```c++
  template<typename T, typename ...Args>
  T& AddObject(Args ...args)
  {
      auto object = std::unique_ptr<T>(std::make_unique<T>(std::forward<Args>(args)...));
      if constexpr (std::is_base_of<Player, T>::value)
      {
        player = object.get();
      }
      T& objectRef = *object.get();
      static_cast<Object&>(objectRef).SetId(lastObjectID);

      objectMap[lastObjectID] = std::move(object);
      objectMap[lastObjectID].get()->SetId(lastObjectID++);

      return objectRef;
  }
  ```

## Templates

  * Template is the method which helps us not repeating same code function for different data type input and output by making compiler define data type of template parameters. The reason why this is important is, we do not need to write same code for different data type input and outputs. This works during compile time. Compiler does type checking so that they put proper data types into source code.

  ```c++
  template<typename T, typename ...Args>
  T& AddObject(Args ...args)
  {
      auto object = std::unique_ptr<T>(std::make_unique<T>(std::forward<Args>(args)...));
      if constexpr (std::is_base_of<Player, T>::value)
      {
        player = object.get();
      }
      T& objectRef = *object.get();
      static_cast<Object&>(objectRef).SetId(lastObjectID);

      objectMap[lastObjectID] = std::move(object);
      objectMap[lastObjectID].get()->SetId(lastObjectID++);

      return objectRef;
  }
  ```

## STL Containers + Iterators + Algorithms

  * What is this?
  	* STL Containers: Like array, container is the collection of elements which has same data types
  	* STL Iterators: Like pointer in array, this indicates sequence of elements in container
  	* STL Algorithms: Algorithm which uses STL Iterators to get specific result after calculate algorithm

  * Why is this important?
  	* By using STL, we can organize variables well as much as using an array
  	* Moreover, STL Algorithm helps programmers use values in STL container with shorter and easier way compared with normal loop or other ways

  * How does it work?
  	* STL is basically set of template classes. If we use standard library format, it stores value as a form of data structure. By using iterator, algorithm access to the value and do work defined by algorithm function.

  ```c++
  private:
    int                                    lastObjectID = 0;
    std::map<int, std::unique_ptr<Object>> objectMap;
    std::vector<int>                       objectsToBeDeleted;
    Player*                                player = nullptr;
  ```

  ```c++
  void ObjectManager::Update()
  {
    std::for_each(objectMap.begin(), objectMap.end(), [&](auto& obj) { obj.second->Update(); });

    std::for_each(objectsToBeDeleted.begin(), objectsToBeDeleted.end(), [&](int id) { objectMap.erase(id); });
    objectsToBeDeleted.clear();
  }
  ```
