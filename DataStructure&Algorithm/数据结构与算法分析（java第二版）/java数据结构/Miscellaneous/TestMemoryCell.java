
    public class TestMemoryCell
    {
        public static void main( String [ ] args )
        {
            MemoryCell m = new MemoryCell( );

/* 1*/      m.write( new Integer( 5 ) );
/* 2*/      System.out.println( "Contents are: " +
/* 3*/                          ( (Integer) m.read( ) ).intValue( ) );
        }
    }

