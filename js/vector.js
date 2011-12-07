
// function vectorFactory()
// {

 function create3N( x, y, z ) { return [ x, y, z ] ; }


 function assign3N( v, x, y, z ) { v[ 0 ] = x ; v[ 1 ] = y ; v[ 2 ] = z ; }
 function assign( v, w ) { v[ 0 ] = w[ 0 ] ; v[ 1 ] = w[ 1 ] ; v[ 2 ] = w[ 2 ] ; }

 function inc( v, w ) { v[ 0 ] += w[ 0 ] ; v[ 1 ] += w[ 1 ] ; v[ 2 ] += w[ 2 ] ; }
 function dec( v, w ) { v[ 0 ] -= w[ 0 ] ; v[ 1 ] -= w[ 1 ] ; v[ 2 ] -= w[ 2 ] ; }

 function plus( v, w )  { return [ v[ 0 ] + w[ 0 ], v[ 1 ] + w[ 1 ], v[ 2 ] + w[ 2 ] ] ; }
 function minus( v, w ) { return [ v[ 0 ] - w[ 0 ], v[ 1 ] - w[ 1 ], v[ 2 ] - w[ 2 ] ] ; }

 function dotProd( v, w ) { return  v[ 0 ] * w[ 0 ] + v[ 1 ] * w[ 1 ] + v[ 2 ] * w[ 2 ] ; }

 function crossProd( v, w ) { return [   v[ 1 ] * w[ 2 ] - v[ 2 ] * w[ 1 ] ,    v[ 2 ] * w[ 0 ] - v[ 0 ] * w[ 2 ],    v[ 0 ] * w[ 1 ] - v[ 1 ] * w[ 0 ]    ] ; } 

 function length2( v ) { return dotProd( v, v ) ; } 
 function length( v ) { return Math.sqrt( length2( v ) ) ; } 
 function normalize( v ) { scaleDown( v, length( v ) ) ; } 


 function scaleUp( v, n )    { v[ 0 ] *= n ; v[ 1 ] *= n ; v[ 2 ] *= n ; }
 function scaleDown( v, n )  { v[ 0 ] /= n ; v[ 1 ] /= n ; v[ 2 ] /= n ; }

 function eq( v, w )  { return v[ 0 ] == w[ 0 ] && v[ 1 ] == w[ 1 ] && v[ 2 ] == w[ 2 ] ; } 
 function neq( v, w ) { return v[ 0 ] != w[ 0 ] || v[ 1 ] != w[ 1 ] || v[ 2 ] != w[ 2 ] ; } 

 // if( !this[ 'exports' ] ) var exports = {} ;

 exports.create3N = create3N ;
 exports.assign = assign ;
 exports.inc = inc ;
 exports.dec = dec ;
 exports.plus = plus ;
 exports.minus = minus ;
 exports.dotProd = dotProd ;
 exports.crossProd = crossProd ;
 exports.length2 = length2 ;
 exports.length = length ;
 exports.normalize = normalize ;
 exports.scaleUp = scaleUp ;
 exports.scaleDown = scaleDown ;
 exports.eq = eq ;
 exports.neq = neq ;
 /*
 return exports ;
 
} ;


if( this[ 'define' ] )
  {
   define( [], vectorFactory ) ;
  
  } 
else vectorFactory() ;


*/