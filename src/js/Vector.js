

this.Vector = function (x, y, z){
  this.x = x;
  this.y = y;
  this.z = z;
  
  this.normalise = function(){
    //FIXME: make an ogrejs.math lib?
    var fLength = Math.sqrt( x * x + y * y + z * z );
    
    if ( fLength != 0 ) {
      var fInvLength = 1.0 / fLength;
      x *= fInvLength;
      y *= fInvLength;
      z *= fInvLength;
    }
  };
  
  this.crossProduct = function(rkVector){
    return new Vector(y * rkVector.z - z * rkVector.y,
      z * rkVector.x - x * rkVector.z,
      x * rkVector.y - y * rkVector.x);
  };
};
