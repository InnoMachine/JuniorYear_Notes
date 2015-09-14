import DataStructures.Comparable;
import DataStructures.MyInteger;

public class Fig02_09
{
        public static final int NOT_FOUND = -1;

/* START: Fig02_09.txt*/
        /**
         * Performs the standard binary search.
         * @return index where item is found, or -1 if not found
         */
        public static int binarySearch( Comparable [ ] a, Comparable x )
        {
/* 1*/      int low = 0, high = a.length - 1;

/* 2*/      while( low <= high )
            {
/* 3*/          int mid = ( low + high ) / 2;

/* 4*/          if( a[ mid ].compareTo( x ) < 0 )
/* 5*/              low = mid + 1;
/* 6*/          else if( a[ mid ].compareTo( x ) > 0 )
/* 7*/              high = mid - 1;
                else
/* 8*/              return mid;   // Found
            }
/* 9*/      return NOT_FOUND;     // NOT_FOUND is defined as -1
        }
/* END */

        // Test program
        public static void main( String [ ] args )
        {
            int SIZE = 8;
            Comparable [ ] a = new MyInteger [ SIZE ];
            for( int i = 0; i < SIZE; i++ )
                a[ i ] = new MyInteger( i * 2 );

            for( int i = 0; i < SIZE * 2; i++ )
                System.out.println( "Found " + i + " at " +
                                     binarySearch( a, new MyInteger( i ) ) );
        }
    }
