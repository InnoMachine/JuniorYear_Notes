import java.util.*;
import java.io.*;
import DataStructures.*;
import DataStructures.Comparable;
import DataStructures.LinkedList;

class WordEntry implements Comparable
{
    String        word;
    LinkedList    lines;
    LinkedListItr listEnd;

    public int compareTo( Comparable rhs )
      { return word.compareTo( ((WordEntry)rhs).word ); }

    public String toString( )
    {
         StringBuffer theString = new StringBuffer( );

             // Print the word
         theString.append( word + ":" );

             // Now print the line numbers
         if( lines != null && !lines.isEmpty( ) )
         {
             LinkedListItr itr = lines.first( );
             theString.append( "\t" + itr.retrieve( ) );
             for( itr.advance( ); !itr.isPastEnd( ); itr.advance( ) )
                 theString.append( ", " + itr.retrieve( ) );
         }
         return new String( theString );
    }
}

class Concordance2
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
            BufferedReader inFile = new BufferedReader( new FileReader( args[0 ] ) );
            AvlTree wordMap = new AvlTree( );
            String oneLine;
            WordEntry entry = new WordEntry( );

                // Read the words; add them to wordMap
            for( int lineNum = 1; ( oneLine = inFile.readLine( ) ) != null; lineNum++ )
            {
                StringTokenizer st = new StringTokenizer( oneLine );
                while( st.hasMoreTokens( ) )
                {
                    entry.word = st.nextToken( );
                    WordEntry match = (WordEntry) wordMap.find( entry );

                    if( match == null )
                    {
                        match = new WordEntry( );
                        match.word = entry.word;
                        match.lines = new LinkedList( );
                        match.listEnd = match.lines.zeroth( );
                        wordMap.insert( match );
                    }
                    match.lines.insert( new Integer( lineNum ), match.listEnd );
                    match.listEnd.advance( );
                }
            }

            wordMap.printTree( );
         }
         catch( Exception e )
           { System.err.println( "Error: " + e ); }
    }

}
