# Generated by Django 4.2.7 on 2024-05-04 04:18

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('App', '0001_initial'),
    ]

    operations = [
        migrations.CreateModel(
            name='PostPhoto',
            fields=[
                ('id', models.BigAutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('photo', models.ImageField(upload_to='post_photos/')),
            ],
        ),
        migrations.DeleteModel(
            name='Click',
        ),
    ]
