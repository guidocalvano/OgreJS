


this.StaticManualObject = function(){
  var _staticManualObject = this;
  
  this._vertices = [];
  this._indices = [];
  
  
  this._getLastVertex(){
    return _staticManualObject._vertices[_staticManualObject._vertices.length - 1];
  }
  
  
  
  this.position = function(pos){
    _staticManualObject._vertices.push( {'pos': pos} );
  };
  
  this.normal = function(normal){
    var vertex = _staticManualObject._getLastVertex();
    vertex.normal = normal;
  };
  
  this.tangent = function(tan){
    var vertex = _staticManualObject._getLastVertex();
    vertex.tangent = tan;
  };
  
  this.textureCoord = function(uvw){
    var vertex = _staticManualObject._getLastVertex();
    vertex.textureCoord = uvw;
  };
  
  this.colour = function(col){
    var vertex = _staticManualObject._getLastVertex();
    vertex.colour = col;
  };
  
  this.index = function(idx){
    _staticManualObject._indices.push(idx);
  }
  
  this.triangle = function(i1, i2, i3){
    _staticManualObject._indices.push(i1);
    _staticManualObject._indices.push(i2);
    _staticManualObject._indices.push(i3);
  }
  
  this.quad = function(i1, i2, i3, i4){
    //FIXME: correct?
    _staticManualObject.triangle(i1, i2, i3);
    _staticManualObject.triangle(i3, i4, i1);
  }
};






