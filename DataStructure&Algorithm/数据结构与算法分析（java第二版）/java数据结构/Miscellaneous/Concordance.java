import java.util.*;
import java.io.*;

class Concordance
{
    /**
     * A main routine that:
     * 1. Reads a file containing strings (from args[0])
     * 2. Prints each string, and the lines on which it occurs
     * Skimpy error checks to avoid clogging up the code.
     */
    public static void main( String [ ] args )
    {
        try
        {
            BufferedReader inFile = new BufferedReader( new FileReader( args[0] ) );
            TreeMap wordMap = new TreeMap( );
            String oneLine;

                // Read the words; add them to wordMap
            for( int lineNum = 1; ( oneLine = inFile.readLine( ) ) != null; lineNum++ )
            {
                StringTokenizer st = new StringTokenizer( oneLine );
                while( st.hasMoreTokens( ) )
                {
                    String word = st.nextToken( );
                    LinkedList lines = (LinkedList) wordMap.get( word );
                    if( lines == null )
                    {
                        lines = new LinkedList( );
                        wordMap.put( word, lines );
                    }
                    lines.addLast( new Integer( lineNum ) );
                }
            }

                // Go through the word map
            for( Iterator itr = wordMap.entrySet( ).iterator( ); itr.hasNext( ); )
                printEntry( (Map.Entry) itr.next( ) );
         }
         catch( Exception e )
           { System.err.println( "Error: " + e ); }
    }

    public static void printEntry( Map.Entry entry )
    {
             // Print the word
         System.out.println( entry.getKey( ) + ":" );

             // Now print the line numbers
         Iterator itr = ( (LinkedList)(entry.getValue( )) ).iterator( );
         System.out.print( "\t" + itr.next( ) );
         while( itr.hasNext( ) )
             System.out.print( ", " + itr.next( ) );
         System.out.println( );
    }
}
