#![deny(clippy::all)]

use napi_derive::napi;

#[napi]
pub fn sum(a: i32, b: i32) -> i32 {
  a + b
}

#[napi]
pub fn plus_100(input: u32) -> u32 {
  input + 100
}

#[napi(js_name = "getNumber")]
fn get_number(arg: f64) -> f64 {
  arg * 2.0
}

#[napi(object)]
pub struct Built {
  pub name: String,
  pub version: i32,
}

#[napi]
fn build_object() -> Built {
  Built {
    name: "rust".into(),
    version: 1,
  }
}

#[napi]
fn make_array(n: u32) -> Vec<i32> {
  (0..n as i32).map(|i| i * 10).collect()
}
