//
//  Errors.hpp
//  Rendering
//
//  Created by vlad on 31.01.2019.
//  Copyright © 2019 vlad. All rights reserved.
//

#ifndef Errors_hpp
#define Errors_hpp

#include <stdio.h>

enum fileOpenErrors{
    fileNotExists
};

void fileError(fileOpenErrors);
#endif /* Errors_hpp */
