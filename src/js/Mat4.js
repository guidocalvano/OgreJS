define(function () {

var Mat4 = {};

Mat4.create = function () {
    return new Float32Array(16);
};

Mat4.set = function (A, B) {
    A[00] = B[00];
    A[01] = B[01];
    A[02] = B[02];
    A[03] = B[03];
    A[04] = B[04];
    A[05] = B[05];
    A[06] = B[06];
    A[07] = B[07];
    A[08] = B[08];
    A[09] = B[09];
    A[10] = B[10];
    A[11] = B[11];
    A[12] = B[12];
    A[13] = B[13];
    A[14] = B[14];
    A[15] = B[15];
};

Mat4.setMat3 = function (A, B) {
    A[00] = B[0];
    A[01] = B[1];
    A[02] = B[2];
    A[03] = 0;
    A[04] = B[3];
    A[05] = B[4];
    A[06] = B[5];
    A[07] = 0;
    A[08] = B[6];
    A[09] = B[7];
    A[10] = B[8];
    A[11] = 0;
    A[12] = 0;
    A[13] = 0;
    A[14] = 0;
    A[15] = 1;
};

Mat4.setIdentity = function (A) {
    A[00] = 1;
    A[01] = 0;
    A[02] = 0;
    A[03] = 0;
    A[04] = 0;
    A[05] = 1;
    A[06] = 0;
    A[07] = 0;
    A[08] = 0;
    A[09] = 0;
    A[10] = 1;
    A[11] = 0;
    A[12] = 0;
    A[13] = 0;
    A[14] = 0;
    A[15] = 1;
};

Mat4.setOrtho = function (A, l, r, b, t, n, f) {
    A[00] = 2 / (r - l);
    A[01] = 0;
    A[02] = 0;
    A[03] = 0;
    A[04] = 0;
    A[05] = 2 / (t - b);
    A[06] = 0;
    A[07] = 0;
    A[08] = 0;
    A[09] = 0;
    A[10] = -2 / (f - n);
    A[11] = 0;
    A[12] = -(r + l) / (r - l);
    A[13] = -(t + b) / (t - b);
    A[14] = -(f + n) / (f - n);
    A[15] = 1;
};

Mat4.setFrustum = function (A, l, r, b, t, n, f) {
    A[00] = 2 * n / (r - l);
    A[01] = 0;
    A[02] = 0;
    A[03] = 0;
    A[04] = 0;
    A[05] = 2 * n / (t - b);
    A[06] = 0;
    A[07] = 0;
    A[08] = (r + l) / (r - l);
    A[09] = (t + b) / (t - b);
    A[10] = -(f + n) / (f - n);
    A[11] = -1;
    A[12] = 0;
    A[13] = 0;
    A[14] = -2 * f * n / (f - n);
    A[15] = 0;
};

Mat4.invert = function (A) {
    var A00 = A[00];
    var A10 = A[01];
    var A20 = A[02];
    var A01 = A[04];
    var A11 = A[05];
    var A21 = A[06];
    var A02 = A[08];
    var A12 = A[09];
    var A22 = A[10];
    var A03 = A[12];
    var A13 = A[13];
    var A23 = A[14];
    var det = A00 * A11 * A22 + A01 * A12 * A20 + A02 * A10 * A21
            - A02 * A11 * A20 - A01 * A10 * A22 - A00 * A12 * A21;
    A[00] = (A11 * A22 - A12 * A21) / det;
    A[01] = (A12 * A20 - A10 * A22) / det;
    A[02] = (A10 * A21 - A11 * A20) / det;
    A[04] = (A02 * A21 - A01 * A22) / det;
    A[05] = (A00 * A22 - A02 * A20) / det;
    A[06] = (A01 * A20 - A00 * A21) / det;
    A[08] = (A01 * A12 - A02 * A11) / det;
    A[09] = (A02 * A10 - A00 * A12) / det;
    A[10] = (A00 * A11 - A01 * A10) / det;
    A[12] = -(A[00] * A03 + A[04] * A13 + A[08] * A23);
    A[13] = -(A[01] * A03 + A[05] * A13 + A[09] * A23);
    A[14] = -(A[02] * A03 + A[06] * A13 + A[10] * A23);
};

Mat4.transpose = function (A) {
    var A10 = A[01];
    var A20 = A[02];
    var A30 = A[03];
    var A21 = A[06];
    var A31 = A[07];
    var A32 = A[11];
    A[01] = A[04];
    A[02] = A[08];
    A[03] = A[12];
    A[04] = A10;
    A[06] = A[09];
    A[07] = A[13];
    A[08] = A20;
    A[09] = A21;
    A[11] = A[14];
    A[12] = A30;
    A[13] = A31;
    A[14] = A32;
};

Mat4.multiply = function (A, B) {
    var A00 = A[00];
    var A01 = A[04];
    var A02 = A[08];
    var A03 = A[12];
    var A10 = A[01];
    var A11 = A[05];
    var A12 = A[09];
    var A13 = A[13];
    var A20 = A[02];
    var A21 = A[06];
    var A22 = A[10];
    var A23 = A[14];
    var B00 = B[00];
    var B01 = B[04];
    var B02 = B[08];
    var B03 = B[12];
    var B10 = B[01];
    var B11 = B[05];
    var B12 = B[09];
    var B13 = B[13];
    var B20 = B[02];
    var B21 = B[06];
    var B22 = B[10];
    var B23 = B[14];
    A[00] = A00 * B00 + A01 * B10 + A02 * B20;
    A[01] = A10 * B00 + A11 * B10 + A12 * B20;
    A[02] = A20 * B00 + A21 * B10 + A22 * B20;
    A[04] = A00 * B01 + A01 * B11 + A02 * B21;
    A[05] = A10 * B01 + A11 * B11 + A12 * B21;
    A[06] = A20 * B01 + A21 * B11 + A22 * B21;
    A[08] = A00 * B02 + A01 * B12 + A02 * B22;
    A[09] = A10 * B02 + A11 * B12 + A12 * B22;
    A[10] = A20 * B02 + A21 * B12 + A22 * B22;
    A[12] += A00 * B03 + A01 * B13 + A02 * B23;
    A[13] += A10 * B03 + A11 * B13 + A12 * B23;
    A[14] += A20 * B03 + A21 * B13 + A22 * B23;
};

Mat4.rotate = function (A, x, y, z) {
    if (x != 0) {
        var A01 = A[04];
        var A02 = A[08];
        var A11 = A[05];
        var A12 = A[09];
        var A21 = A[06];
        var A22 = A[10];
        var cosx = Math.cos(x);
        var sinx = Math.sin(x);
        A[04] = A01 * cosx + A02 * sinx;
        A[05] = A11 * cosx + A12 * sinx;
        A[06] = A21 * cosx + A22 * sinx;
        A[08] = A01 * -sinx + A02 * cosx;
        A[09] = A11 * -sinx + A12 * cosx;
        A[10] = A21 * -sinx + A22 * cosx;
    }
    if (y != 0) {
        var A00 = A[00];
        var A02 = A[08];
        var A10 = A[01];
        var A12 = A[09];
        var A20 = A[02];
        var A22 = A[10];
        var cosy = Math.cos(y);
        var siny = Math.sin(y);
        A[00] = A00 * cosy + A02 * -siny;
        A[01] = A10 * cosy + A12 * -siny;
        A[02] = A20 * cosy + A22 * -siny;
        A[08] = A00 * siny + A02 * cosy;
        A[09] = A10 * siny + A12 * cosy;
        A[10] = A20 * siny + A22 * cosy;
    }
    if (z != 0) {
        var A00 = A[00];
        var A01 = A[04];
        var A10 = A[01];
        var A11 = A[05];
        var A20 = A[02];
        var A21 = A[06];
        var cosz = Math.cos(z);
        var sinz = Math.sin(z);
        A[00] = A00 * cosz + A01 * sinz;
        A[01] = A10 * cosz + A11 * sinz;
        A[02] = A20 * cosz + A21 * sinz;
        A[04] = A00 * -sinz + A01 * sinz;
        A[05] = A10 * -sinz + A11 * cosz;
        A[06] = A20 * -sinz + A21 * cosz;
    }
};

Mat4.scale = function (A, x, y, z) {
    A[00] *= x;
    A[01] *= x;
    A[02] *= x;
    A[04] *= y;
    A[05] *= y;
    A[06] *= y;
    A[08] *= z;
    A[09] *= z;
    A[10] *= z;
};

Mat4.translate = function (A, x, y, z) {
    A[12] += A[00] * x + A[04] * y + A[08] * z;
    A[13] += A[01] * x + A[05] * y + A[09] * z;
    A[14] += A[02] * x + A[06] * y + A[10] * z;
    A[15] += A[03] * x + A[07] * y + A[11] * z;
};

Mat4.apply = function (A, b) {
    var b0 = b[0];
    var b1 = b[1];
    var b2 = b[2];
    var b3 = b[3];
    b[0] = A[00] * b0 + A[04] * b1 + A[08] * b2 + A[12] * b3;
    b[1] = A[01] * b0 + A[05] * b1 + A[09] * b2 + A[13] * b3;
    b[2] = A[02] * b0 + A[06] * b1 + A[10] * b2 + A[14] * b3;
    b[3] = A[03] * b0 + A[07] * b1 + A[11] * b2 + A[15] * b3;
};

return Mat4;

});
