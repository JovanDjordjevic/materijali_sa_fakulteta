var Person = /** @class */ (function () {
    function Person(name) {
        this.name = name;
    }
    return Person;
}());
var p = new Person("Pera");
document.body.innerHTML = p.name;
