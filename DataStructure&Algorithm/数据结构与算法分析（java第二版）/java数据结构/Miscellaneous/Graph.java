import java.util.*;
import java.io.*;

class Vertex
{
    String     name;   // Vertex name
    LinkedList adj;    // Adjacent vertices
    int        dist;   // Cost
    Vertex     path;   // Previous vertex on shortest path

    public Vertex( String nm )
      { name = nm; adj = new LinkedList( ); reset( ); }

    public void reset( )
      { dist = Graph.INFINITY; path = null; }    
}

class Graph
{
    public static final int INFINITY = Integer.MAX_VALUE;
    private HashMap vertexMap = new HashMap( );    // Maps vertices to internal Vertex

    public void addEdge( String sourceName, String destName )
    {
        Vertex v = getVertex( sourceName );
        Vertex w = getVertex( destName );
        v.adj.add( w );
    }

    public void printPath( String destName ) throws NoSuchElementException
    {
        Vertex w = (Vertex) vertexMap.get( destName );
        if( w == null )
            throw new NoSuchElementException( "Destination vertex not found" );
        else if( w.dist == INFINITY )
            System.out.println( destName + " is unreachable" );
        else
        {
            printPath( w );
            System.out.println( );
        }
    }

      // If vertexName is not present, add it to vertexMap.
      // In either case, return the Vertex.
    private Vertex getVertex( String vertexName )
    {
        Vertex v = (Vertex) vertexMap.get( vertexName );
        if( v == null )
        {
            v = new Vertex( vertexName );
            vertexMap.put( vertexName, v );
        }
        return v;
    }

    private void printPath( Vertex dest )
    {
        if( dest.path != null )
        {
            printPath( dest.path );
            System.out.print( " to " );
        }
        System.out.print( dest.name );
    }

    private void clearAll( )
    {
        for( Iterator itr = vertexMap.values( ).iterator( ); itr.hasNext( ); )
            ( (Vertex)itr.next( ) ).reset( );
    }

    public void unweighted( String startName ) throws NoSuchElementException
    {
        clearAll( ); 

        Vertex start = (Vertex) vertexMap.get( startName );
        if( start == null )
            throw new NoSuchElementException( "Start vertex not found" );

        LinkedList q = new LinkedList( );
        q.addLast( start ); start.dist = 0;

        while( !q.isEmpty( ) )
        {
            Vertex v = (Vertex) q.removeFirst( );

            for( Iterator itr = v.adj.iterator( ); itr.hasNext( ); )
            {
                Vertex w = (Vertex) itr.next( );
                if( w.dist == INFINITY )
                {
                    w.dist = v.dist + 1;
                    w.path = v;
                    q.addLast( w );
                }
            }
        }
    }

    /**
     * Process a request; return false if end of file.
     */
    public static boolean processRequest( BufferedReader in, Graph g )
    {
        String startName = null;
        String destName = null;

        try
        {
            System.out.println( "Enter start node:" );
            if( ( startName = in.readLine( ) ) == null )
                return false;
            System.out.println( "Enter destination node:" );
            if( ( destName = in.readLine( ) ) == null )
                return false;

            g.unweighted( startName );
            g.printPath( destName );
        }
        catch( Exception e )
          { System.err.println( e ); }
        return true;
    }

    /**
     * A main routine that:
     * 1. Reads a file containing edges (supplied as a command-line parameter);
     * 2. Forms the graph;
     * 3. Repeatedly prompts for two vertices and
     *    runs the shortest path algorithm.
     * The data file is a sequence of lines of the format
     *    source destination.
     */
    public static void main( String [ ] args )
    {
        Graph g = new Graph( );
        try
        {
            FileReader fin = new FileReader( args[0] );
            BufferedReader graphFile = new BufferedReader( fin );

            // Read the edges and insert
            String line;
            while( ( line = graphFile.readLine( ) ) != null )
            {
                StringTokenizer st = new StringTokenizer( line );

                try
                {
                    if( st.countTokens( ) != 2 )
                        throw new Exception( );
                    String source  = st.nextToken( );
                    String dest    = st.nextToken( );
                    g.addEdge( source, dest );
                }
                catch( Exception e )
                  { System.err.println( e + " " + line ); }
             }
         }
         catch( Exception e )
           { System.err.println( e ); }

         System.out.println( "File read" );

         BufferedReader in = new BufferedReader( new InputStreamReader( System.in ) );
         while( processRequest( in, g ) )
             ;
    }
}
