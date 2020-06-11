all: MaxSubRange jpr14e TestCell TestSeq

MaxSubRange: MaxSubRange.o Cell.o
        g++ -std=c++11 -o MaxSubRange MaxSubRange.o Cell.o

MaxSubRange.o: MaxSubRange.cpp Cell.h NSequence.h FunClassTemp.h
        g++ -std=c++11 -c MaxSubRange.cpp

Cell.o: Cell.cpp Cell.h
        g++ -std=c++11 -c Cell.cpp

jpr14e: jpr14e_driver.o Cell.o
        g++ -std=c++11 -o jpr14e jpr14e_driver.o Cell.o

jpr14e_driver.o: jpr14e_driver.cpp Cell.h NSequence.h FunClassTemp.h
        g++ -std=c++11 -c jpr14e_driver.cpp

TestCell: TestCell.o Cell.o
        g++ -std=c++11 -o TestCell TestCell.o Cell.o

TestCell.o: TestCell.cpp Cell.h FunClassTemp.h
        g++ -std=c++11 -c TestCell.cpp

TestSeq: TestSeq.o Cell.o
        g++ -std=c++11 -o TestSeq TestSeq.o Cell.o

TestSeq.o: TestSeq.cpp Cell.h NSequence.h FunClassTemp.h
        g++ -std=c++11 -c TestSeq.cpp

clean:
        rm *.o TestSeq TestCell jpr14e MaxSubRange
