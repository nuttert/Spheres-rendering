//
//  Errors.cpp
//  Rendering
//
//  Created by vlad on 31.01.2019.
//  Copyright © 2019 vlad. All rights reserved.
//

#include "Errors.hpp"
#include <iostream>
void fileError(fileOpenErrors error){
    switch (error) {
        case fileNotExists:
            std::cout << "File not exists"<<std::endl;
            break;
        default:break;
    }
}
