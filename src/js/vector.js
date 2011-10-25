

function create3N( x, y, z ) { return [ x, y, z ] ; }


function assign3N( v, x, y, z ) { v[ 0 ] = x ; v[ 1 ] = y ; v[ 2 ] = z ; }
function assign( v, w ) { v[ 0 ] = w[ 0 ] ; v[ 1 ] = w[ 1 ] ; v[ 2 ] = w[ 2 ] ; }

function inc( v, w ) { v[ 0 ] += w[ 0 ] ; v[ 1 ] += w[ 1 ] ; v[ 2 ] += w[ 2 ] ; }
function dec( v, w ) { v[ 0 ] -= w[ 0 ] ; v[ 1 ] -= w[ 1 ] ; v[ 2 ] -= w[ 2 ] ; }

function plus( v, w )  { return [ v[ 0 ] + w[ 0 ], v[ 1 ] + w[ 1 ], v[ 2 ] + w[ 2 ] ] ; }
function minus( v, w ) { return [ v[ 0 ] - w[ 0 ], v[ 1 ] - w[ 1 ], v[ 2 ] - w[ 2 ] ] ; }

function inProd( v, w ) { return  v[ 0 ] * w[ 0 ] + v[ 1 ] * w[ 1 ] + v[ 2 ] * w[ 2 ] ; }

function scaleUp( v, n )    { v[ 0 ] *= n ; v[ 1 ] *= n ; v[ 2 ] *= n ; }
function scaleDown( v, n )  { v[ 0 ] /= n ; v[ 1 ] /= n ; v[ 2 ] /= n ; }

function eq( v, w )  { return v[ 0 ] == w[ 0 ] && v[ 1 ] == w[ 1 ] && v[ 2 ] == w[ 2 ] ; } 
function neq( v, w ) { return v[ 0 ] != w[ 0 ] || v[ 1 ] != w[ 1 ] || v[ 2 ] != w[ 2 ] ; } 
