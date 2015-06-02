#include <iostream>
#include <vector>



int main() {
    
    //    std::vector<int> leftHand;
    //    leftHand.push_back(1);
    //    leftHand.push_back(2);
    //    leftHand.push_back(3);
    //    leftHand.push_back(5);
    //    leftHand.push_back(6);
    //
    //    if(leftHand.size() > 3){}
    //
    //    for (auto c : leftHand)
    //        std::cout << c << ' ';
    
    int leftHand = 0;
    int rightHand = 0;
    int lastLostHand = 0;
    int newHand = 0;
    
    int handsSize = 0;
    
    if(handsSize >= 1){
        std::cout << "Fist Hand \n" ;
        rightHand = 1;
    }
    
    std::cout << "r :" << rightHand << " l:" << leftHand << " ll:" << lastLostHand << " HS :" << handsSize <<std::endl;
    
    handsSize++;
    
    if(handsSize == 1){
        std::cout << "Fist Hand \n" ;
        rightHand = 1;
    }
    
    std::cout << "r :" << rightHand << " l:" << leftHand << " ll:" << lastLostHand << " HS :" << handsSize <<std::endl;
    handsSize++;
    leftHand = 2;
    
    std::cout << "r :" << rightHand << " l:" << leftHand << " ll:" << lastLostHand << " HS :" << handsSize <<std::endl;
    
    std::cout << "Lost hand :" << leftHand << std::endl;
    lastLostHand = 2;
    newHand = 3;
    handsSize++;
    
    if(lastLostHand == leftHand){
        leftHand = newHand;
    }else if(lastLostHand == rightHand){
        rightHand = newHand;
    }
    
    std::cout << "r :" << rightHand << " l:" << leftHand << " ll:" << lastLostHand << " HS :" << handsSize <<std::endl;
    
    std::cout << "Lost hand :" << leftHand << std::endl;
    lastLostHand = 1;
    newHand = 4;
    handsSize++;
    
    if(lastLostHand == leftHand){
        leftHand = newHand;
    }else if(lastLostHand == rightHand){
        rightHand = newHand;
    }
    
    std::cout << "r :" << rightHand << " l:" << leftHand << " ll:" << lastLostHand << " HS :" << handsSize <<std::endl;
    
    
}
