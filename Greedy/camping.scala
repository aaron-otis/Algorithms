import scala.io.Source
import scala.io.StdIn.readInt

object Camping {
    val files = Vector("test_a.txt", "test_b.txt", "test_c.txt", "custom1.txt")

    def buildMap(input: Int):Map[Int, (Int, Int, Int)] = {
        val map = new scala.collection.mutable.HashMap[Int, (Int, Int, Int)]()

        Source.fromFile(files(input)).getLines.foreach( line => {
            line.split(" ") match {
                case Array(i, j) => {
                    val key = i.substring(0, i.length - 1).toInt
                    j.substring(1, j.length - 1).split(",") match {
                        case Array(x, y, z) => {
                            val tup = (x.toInt, y.toInt, z.toInt)
                            map += (key -> tup)
                        }
                        case _ => println("Tuple extraction failed!")
                    }
                }
                case _ => println("String split failed!")
            }
        })
        new scala.collection.immutable.HashMap() ++ map
    }

    def solve(map: Map[Int, (Int, Int, Int)]): (Seq[Int], Int) = {
        val sequence = List()
        var max = 0

        def findNext(subMap: Map[Int, (Int, Int, Int)], list: List[Int], 
         total: Int): (Map[Int, (Int, Int, Int)], Seq[Int], Int) = {

            if (subMap.isEmpty)
                return Tuple3(subMap, list, total + max)
            else {
                var key = 0
                var localMax = 0

                subMap foreach { k => {
                    if (k._2._2 + k._2._3 > localMax) {
                        localMax = k._2._2 + k._2._3
                        key = k._1
                    }
                }}
                max -= subMap(key)._1
                max = if (localMax > max) localMax else max
                return findNext(subMap - key, list ++ List(key), 
                 total + subMap(key)._1)
            }
        }
        val tup: (Map[Int, (Int, Int, Int)], Seq[Int], Int) = findNext(map, 
         sequence, 0)
        return Tuple2(tup._2, tup._3)
    }

    def main(args: Array[String]) {
        var finished = false

        do {
            println()
            for (i <- 1 to files.length) println(i + ": " + files(i - 1))
            println("Pick a file to test. Enter 0 to exit.")
            val input =  readInt() 

            if (input > 0 && input <= files.length)
                println(solve(buildMap(input - 1)))
            else if (input == 0) 
                finished = true
            else
                println("Invalid input")
                
        } while (!finished)

        println("Goodbye!")
    }
}
