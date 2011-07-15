

this.SceneNode = function(parent){
  var _self = this;
  
  this._parent = parent;
  this._entities = [];
  this._nodes = [];
  
  //FIXME: how do we handle null parents?
  this._handle = new ogrejs.juice.SceneNode(parent._handle);
  
  
  this._addChild = function(child, container, addHandle) {
    container.push(child);
    addHandle(child._handle);
  };
  
  this._removeChild = function(child, container, removeHandle){
    for (var i = 0; i < container.length){
      if (container[i] == child) {
        container.splice(i,1);
        removeHandle(child._handle);
        return;
      }
    }
    assert("child not found");
  };
  
  this._addEntity = function(entity){
    assert(entity != null);
    assert(entity instanceof Entity);
    
    _self._addChild(entity, _self._handle.addEntity);
  };
  
  this._removeEntity = function(entity){
    assert(entity != null);
    assert(entity instanceof Entity);
    
    _self.removeChild(entity, _self._entities, _self._handle.removeEntity);
  };
  
  this._addNode = function(node){
    assert(node != null);
    
    assert(node instanceof SceneNode);
    
    _self._addChild(node, _self._handle.addNode);
  };
  
  this._removeNode = function(node){
    assert(node != null);
    assert(node instanceof SceneNode);
    
    _self.removeChild(node, _self._nodes, _self._handle.removeNode);
  };
  
  
  this._doParent = function(){
    if ( _self._parent != null ){
      //sanity
      assert(parent instanceof SceneNode);
      
      _self._parent._addNode(_self);
    }
  };
  
  this._unParent = function(){
    if ( _self._parent != null ){
      //sanity
      assert(parent instanceof SceneNode);
      
      _self._parent._removeNode(_self);
      
      _self._parent = null;
    }
  };
  
  
  
  
  
  
  
  this.setPosition = function(pos) {
    assert(pos instanceof Vector);
    _self._handle.setPosition( pos.cook() );
  };
  
  this.setParent = function(parent){
    assert(parent instanceof SceneNode, "parent must be a SceneNode");
    
    _self._unParent();
    
    _self._parent = parent;
    
    _self._doParent();
  };
};






