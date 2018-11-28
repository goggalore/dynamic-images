//
//  main.swift
//  DynamicImages
//
//  Created by June Crane on 11/28/18.
//  Copyright © 2018 June Crane. All rights reserved.
//

import Foundation
import CoreGraphics

// the function that we will call
func getLayout(images: [(String, CGSize)]) -> [[String: CGSize]] {
   
    // the following constants are to be changed in the future upon discussion with iOS team
    let max : CGFloat = 500.0
    let gap : CGFloat = 0.0
    let width : CGFloat = 1000.0
    
    // helper closure functions
    func getHeight(row: [(String, CGSize)]) -> CGFloat {
        
        var sum : CGFloat = 0.0
    
        for i in row {
            switch i {
            case let (_, dimension):
                sum += dimension.width / dimension.height
            }
        }
        
        // don't divide by 0!
        if sum == 0.0 {
            return 0.0
        }
        
        let n = CGFloat(row.count)
        return (width - gap*(n - 1)) / sum
    }
    
    func finish(row: [(String, CGSize)], height: CGFloat) -> [String: CGSize] {
        // "finishes" the mathematical logic, i.e. formats the row now that the max constraint has been satisfied
        
        var formatted: [String: CGSize] = [:]
        
        for i in row {
            switch i {
            case let (identifier, dimension):
                let wp = height * (dimension.width / dimension.height)
                formatted[identifier] = CGSize.init(width: wp, height: height)
            }
        }
       
        return formatted
   }

    
    // main logic
    var layout: [[String: CGSize]] = []
    var row: [(String, CGSize)] = []
    
    for image in images {
        row.append(image)
        let height = getHeight(row: row);
        if (height <= max) {
            layout.append(finish(row: row, height: height))
            row = []
        }
    }
    
    // deal with trailing images
    if !row.isEmpty {
        let height = getHeight(row: row);
        layout.append(finish(row: row, height: height))
    }
    
    return layout
}
