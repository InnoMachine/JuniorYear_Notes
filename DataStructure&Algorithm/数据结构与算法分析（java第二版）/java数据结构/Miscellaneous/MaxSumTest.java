public final class MaxSumTest
{
/* START: Fig02_05.txt */
        /**
         * Cubic maximum contiguous subsequence sum algorithm.
         */
        public static int maxSubSum1( int [ ] a )
        {
/* 1*/      int maxSum = 0;

/* 2*/      for( int i = 0; i < a.length; i++ )
/* 3*/          for( int j = i; j < a.length; j++ )
                {
/* 4*/              int thisSum = 0;

/* 5*/              for( int k = i; k <= j; k++ )
/* 6*/                  thisSum += a[ k ];

/* 7*/              if( thisSum > maxSum )
/* 8*/                  maxSum   = thisSum;
                }

/* 9*/      return maxSum;
        }
/* END */


/* START: Fig02_06.txt */
        /**
         * Quadratic maximum contiguous subsequence sum algorithm.
         */
        public static int maxSubSum2( int [ ] a )
        {
/* 1*/      int maxSum = 0;

/* 2*/      for( int i = 0; i < a.length; i++ )
            {
/* 3*/          int thisSum = 0;
/* 4*/          for( int j = i; j < a.length; j++ )
                {
/* 5*/              thisSum += a[ j ];

/* 6*/              if( thisSum > maxSum )
/* 7*/                  maxSum = thisSum;
                }
            }

/* 8*/      return maxSum;
        }
/* END */

/* START: Fig02_07.txt */
        /**
         * Recursive maximum contiguous subsequence sum algorithm.
         * Finds maximum sum in subarray spanning a[left..right].
         * Does not attempt to maintain actual best sequence.
         */
        private static int maxSumRec( int [ ] a, int left, int right )
        {
/* 1*/      if( left == right )  // Base case
/* 2*/          if( a[ left ] > 0 )
/* 3*/              return a[ left ];
                else
/* 4*/              return 0;

/* 5*/      int center = ( left + right ) / 2;
/* 6*/      int maxLeftSum  = maxSumRec( a, left, center );
/* 7*/      int maxRightSum = maxSumRec( a, center + 1, right );

/* 8*/      int maxLeftBorderSum = 0, leftBorderSum = 0;
/* 9*/      for( int i = center; i >= left; i-- )
            {
/*10*/          leftBorderSum += a[ i ];
/*11*/          if( leftBorderSum > maxLeftBorderSum )
/*12*/              maxLeftBorderSum = leftBorderSum;
            }

/*13*/      int maxRightBorderSum = 0, rightBorderSum = 0;
/*14*/      for( int i = center + 1; i <= right; i++ )
            {
/*15*/          rightBorderSum += a[ i ];
/*16*/          if( rightBorderSum > maxRightBorderSum )
/*17*/              maxRightBorderSum = rightBorderSum;
            }

/*18*/      return max3( maxLeftSum, maxRightSum,
/*19*/                   maxLeftBorderSum + maxRightBorderSum );
        }

        /**
         * Driver for divide-and-conquer maximum contiguous
         * subsequence sum algorithm.
         */
        public static int maxSubSum3( int [ ] a )
        {
            return maxSumRec( a, 0, a.length - 1 );
        }
/* END */

        /**
         * Return maximum of three integers.
         */
        private static int max3( int a, int b, int c )
        {
            return a > b ? a > c ? a : c : b > c ? b : c;
        }

/* START: Fig02_08.txt */
        /**
         * Linear-time maximum contiguous subsequence sum algorithm.
         */
        public static int maxSubSum4( int [ ] a )
        {
/* 1*/      int maxSum = 0, thisSum = 0;

/* 2*/      for( int j = 0; j < a.length; j++ )
            {
/* 3*/          thisSum += a[ j ];

/* 4*/          if( thisSum > maxSum )
/* 5*/              maxSum = thisSum;
/* 6*/          else if( thisSum < 0 )
/* 7*/              thisSum = 0;
            }

/* 8*/      return maxSum;
        }
/* END */

        /**
         * Simple test program.
         */
        public static void main( String [ ] args )
        {
            int a[ ] = { 4, -3, 5, -2, -1, 2, 6, -2 };
            int maxSum;

            maxSum = maxSubSum1( a );
            System.out.println( "Max sum is " + maxSum );
            maxSum = maxSubSum2( a );
            System.out.println( "Max sum is " + maxSum );
            maxSum = maxSubSum3( a );
            System.out.println( "Max sum is " + maxSum );
            maxSum = maxSubSum4( a );
            System.out.println( "Max sum is " + maxSum );
        }
    }

