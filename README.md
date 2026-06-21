# C DIR STRUCTURE

A very simple c program, that can create parameterized directory structures.

## Example

You have to create a `template.xml` file right next to the executable. 

In here, you can currently only describe the first child-level directories of a module directory.

```xml
<template>
  <dirs name="!ROOT/!MODULES">
    <dir name="0_scripts"/>
    <dir name="1_exercises"/>
    <dir name="2_notes"/>
  </dirs>
</template>
```

`!ROOT`: is the directory parameter for the very first prompted directory name, the root name.
`!MODULES`: is the modules paramter for the many prompted directory names, called modules.

This could result in...
```
"EXAMPLE_ROOT"/
- "MODULE_1"/
- - "0_scripts"/
- - "1_exercises"/
- - "2_notes"/
- "MODULE_2"/
- - "0_scripts"/
- - "1_exercises"/
- - "2_notes"/
- "MODULE_3"/
- - "0_scripts"/
- - "1_exercises"/
- - "2_notes"/
```

> [!NOTE]
> I am not a professional C developer, just trying to develop small simple tools with this language to get a better feel for the language, experiment a litte and get jobs done
