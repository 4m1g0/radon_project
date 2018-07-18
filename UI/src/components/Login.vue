<template>
<div>
    <div class="row">
        <div class="input-field col offset-s1 s10">
          <input v-model="token" id="token" type="text" class="validate" @keyup.enter="login">
          <label for="token">Token</label>
        </div>
      </div>
      <!--<div class="row">
        <div class="input-field col offset-s1 s10">
          <input id="password" type="password" class="validate">
          <label for="password">Password</label>
        </div>
      </div>-->
      <div class="row">
        <div class="input-field col offset-s2 s8">
          <a class="waves-effect waves-light btn-large" @click="login">Login</a>
        </div>
      </div>
</div>
    
</template>

<script>
import { serverBus } from '../main';

export default {
    data() {
        return {
            token: ""
        }
    },
    mounted(){
        this.$emit('set_loading', false);
    },
    methods: {
        login(){
            this.$cookie.set('token', this.token);
            serverBus.$emit('login');
        }
    }
}
</script>

<style>
.btn-large{
    width: 100%;
}
</style>
